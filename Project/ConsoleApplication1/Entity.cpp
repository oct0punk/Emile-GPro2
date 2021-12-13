#include "Entity.h"
#include "Tool.hpp"

void Entity::update(double dt) {
	if (!visible) return;
	if (cmds) applyCmdInterp(cmds, dt);

	sf::Vector2f move = getPosition();
	move.x += dx * dt;
	move.y += dy * dt;
	setPosition(move.x, move.y);

}

void Entity::draw(sf::RenderWindow& win) {
	if (visible)
		win.draw(*spr);
}

Cmd* Entity::applyCmdInterp(Cmd* cmd, double dt) {
	//dt = 1.0f / 60.0f * 0.1;
	bool destroy = false;
	switch (cmd->type) {
	case Move:
	{
		sf::Vector2f dir = sf::Vector2f(targetPos - getPosition());
		if (Magnitude(dir) < cmds->value * dt) {
			destroy = true;
			break;
		}
		Normalize(&dir);
		dir *= cmds->value * (float)dt;
		dir += getPosition();
		setPosition(dir.x, dir.y);
	}
	break;
	case Rotate:
		break;
	default:
		destroy = true;
		break;
	}


	if (!destroy) {
		return cmd;
	}
	else {
		cmd = cmd->popFirst();
		return cmd;
	}
}



void PlayerPad::update(double dt) {
}

void PlayerPad::draw(sf::RenderWindow& win) {
	if (visible)
		win.draw(*spr);

}


void Laser::create(float _px, float _py, float _dx, float _dy) {
	if (reloading > 0.0f) return;
	reloading = reloadTime;
	sf::Vector2f dir(_dx, _dy);
	Normalize(&dir);
	float dx = dir.x;
	float dy = dir.y;
	for (int i = 0; i < px.size(); ++i) {
		if (!alive[i]) {
			px[i] = _px;
			py[i] = _py;
			this->dx[i] = dx;
			this->dy[i] = dy;
			alive[i] = true;
			return;
		}
	}
	px.push_back(_px);
	py.push_back(_py);
	this->dx.push_back(dx);
	this->dy.push_back(dy);
	alive.push_back(true);
}

void Laser::ChangeDirection(int idx, float x, float y) {
	sf::Vector2f dir(x, y);
	Normalize(&dir);
	dx[idx] = dir.x;
	dy[idx] = dir.y;
}

void Laser::update(double dt) {
	if (reloading > 0.0f) {
		reloading -= dt;
	}
	for (int i = 0; i < px.size(); ++i) {
		if (alive[i]) {		// Move each shape into (dx ; dy)
			px[i] += dx[i] * speed * dt;
			py[i] += dy[i] * speed * dt;
			if (	// Check if outside screen
				(px[i] > 3000) || (px[i] < -100) ||
				(py[i] > 3000) || (py[i] < -100)
				) {
				alive[i] = false;
			}
		}
	}
}

void Laser::draw(sf::RenderWindow& win) {
	int idx = 0;
	const int sz = px.size();
	while (idx < sz) {
		if (alive[idx]) {
			auto b = spr;
			b->setRotation(atan2(dy[idx], dx[idx]) * 57.2958f);
			b->setPosition(sf::Vector2f(px[idx], py[idx]));
			win.draw(*b);
		}
		idx++;
	}
}



bool CheckCollisionUsingRect(Entity* rect1, Entity* rect2) {
	if (rect1->spr->getGlobalBounds().contains(rect2->getPosition())) {
		float x = rect2->getPosition().x - rect1->getPosition().x;
		float y = rect2->getPosition().y - rect1->getPosition().y;
		float magnitude = sqrt(x * x + y * y);
		x /= magnitude;
		y /= magnitude;

		float w = rect1->spr->getGlobalBounds().width / 2;
		float h = rect1->spr->getGlobalBounds().height / 2;
		magnitude = sqrt(w * w + h * h);
		w /= magnitude;
		h /= magnitude;

		if (abs(x) > w)			rect2->dx *= -1;
		else if (abs(y) > h)	rect2->dy *= -1;
		rect2->spr->setOutlineColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
		rect1->spr->setOutlineColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
		rect2->setPosition(rect2->lastGoodPos.x, rect2->lastGoodPos.y);
		return true;
	}
	rect2->lastGoodPos = rect2->getPosition();
	return false;
}

void Enemy::update(double dt)
{
	Entity::update(dt);

	if (p) {
		if (p->visible) {
			// Look at player
			sf::Vector2f intoP = p->getPosition() - getPosition();
			float targetAngle = atan2(intoP.y, intoP.x) * RadToDeg();
			setRotation(targetAngle);

			// Move into player
			int speed = 300;
			Normalize(&intoP);
			dx = intoP.x * speed;
			dy = intoP.y * speed;
			//dx += Sign(intoP.x) * speed * dt;
			//dy += Sign(intoP.y) * speed * dt;
		}
		else
		{
			SlowDown(200 * dt);
		}
	}
	else
	{
		SlowDown(200 * dt);
	}
}

PlayerPad* Enemy::LookForPlayer(PlayerPad* pp, sf::Image rt, sf::Color clearColor) {

	sf::Vector2f ray = pp->getPosition() - getPosition();	// Raycast from enemy to player
	float distance = Magnitude(ray);
	if (distance < 100)
		return pp;
	Normalize(&ray);
	for (int i = 100; i < distance; i += 5) {

		sf::Vector2f point;
		point.x = getPosition().x + ray.x * i;
		point.y = getPosition().y + ray.y * i;
		if (!visible) return nullptr;
		sf::Color rtc = rt.getPixel(point.x, point.y);		// Check pixel's color along the ray
		if (rtc.toInteger() != clearColor.toInteger()) {
			if (pp->spr->getGlobalBounds().contains(point))	// if pixel in player's bounds
				return pp;									// Player found
			else
				return nullptr;								// Else obstacle
		}
	}
	return nullptr;											// Nothing hit
}

void Enemy::SlowDown(int speed) {
	float zero = 0;
	dx = Sign(dx) < 0 ?
		clamp(zero, dx, dx + speed) :
		clamp(zero, dx - speed, dx);
	dy = Sign(dy) < 0 ?
		clamp(zero, dy, dy + speed) :
		clamp(zero, dy - speed, dy);
}

void Enemy::draw(sf::RenderWindow& win)
{
	Entity::draw(win);
}
