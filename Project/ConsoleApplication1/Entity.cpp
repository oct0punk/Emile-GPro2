#include "Entity.h"
#include "Tool.hpp"
#include "Game.h"
#include "Audio.h"

void Entity::update(double dt) {
	timeSinceLevelStart += dt;
	if (!visible) return;
	if (cmds) applyCmdInterp(cmds, dt);

	sf::Vector2f move = getPosition();
	move.x += dx * dt;
	move.y += dy * dt;
	setPosition(move.x, move.y);

	if (type == EType::Wall)
		Movement(dt * 5);
	}


void Entity::draw(sf::RenderWindow& win) {
	if (visible)
		win.draw(*spr);
}


void Entity::Movement(double dt) {
	dx = sin(timeSinceLevelStart * dt) * 600 * dt;
	dy = cos(timeSinceLevelStart * .2f * dt) * 600 * dt;
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
	if (invincible) {
		invincibleTime -= dt;
		if (invincibleTime <= 0) {
			invincible = false;
			spr->setFillColor(sf::Color(150, 50, 0));
		}
	}
	else
		spr->setFillColor(sf::Color::Transparent);
}


void PlayerPad::draw(sf::RenderWindow& win) {
	if (visible)
		win.draw(*spr);

}


bool PlayerPad::ChangeHealth(int amount) {
	if (invincible) return false;
	health += amount;
	float r = lerp(health / 2, 0, 255);
	float g = lerp(health / 3, 0, 255);
	float b = lerp(health / 1, 0, 255);
	spr->setOutlineColor(sf::Color(r, g, b));
	if (amount < 0) {
		invincible = true;
		invincibleTime = 1.0f;
		spr->setFillColor(sf::Color::Red);
	}
	if (health < 0) {
		visible = false;
		Game::GetInstance()->state = GameState::GameOver;
		return true;
	}
	return false;
}




void Laser::create(float _px, float _py, float _dx, float _dy, float rTime) {
	if (reloading > 0.0f) return;
	reloading = rTime;
	Audio::GetInstance()->Play();

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
			power[i] = 1;
			return;
		}
	}
	px.push_back(_px);
	py.push_back(_py);
	this->dx.push_back(dx);
	this->dy.push_back(dy);
	alive.push_back(true);
	power.push_back(1);
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




bool Enemy::ChangeHealth(int amount) {
	health += amount;
	if (health < 0) {
		visible = false;
		return true;
	}
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
			if (abs(dx + dy) > 0)
				SlowDown(200 * dt);
		}
	}
}

//  Old Raycast //	PlayerPad* Enemy::LookForPlayer(PlayerPad* pp, sf::Image rt, sf::Color clearColor) {
//	
//		sf::Vector2f ray = pp->getPosition() - getPosition();	// Raycast from enemy to player
//		float distance = Magnitude(ray);
//		if (distance < 100)
//			return pp;
//		Normalize(&ray);
//		for (int i = 100; i < distance; i += 5) {
//	
//			sf::Vector2f point;
//			point.x = getPosition().x + ray.x * i;
//			point.y = getPosition().y + ray.y * i;
//			if (!visible) return nullptr;
//			sf::Color rtc = rt.getPixel(point.x, point.y);		// Check pixel's color along the ray
//			if (rtc.toInteger() != clearColor.toInteger()) {
//				if (pp->spr->getGlobalBounds().contains(point))	// if pixel in player's bounds
//					return pp;									// Player found
//				else
//					return nullptr;								// Else obstacle
//			}
//		}
//		return nullptr;											// Nothing hit
//	}
void Enemy::SlowDown(int speed) {
	dx = clamp(0.0f, dx - speed, dx + speed);
	dy = clamp(0.0f, dy - speed, dy + speed);
}




void PlayMode()		{ Game::GetInstance()->state = GameState::Playing; }
void RetryButton()	{ Game::GetInstance()->Reset(); }

Button::Button(sf::Shape* _spr, sf::Text* txt) : Entity(EType::UI, _spr) {
	text = *txt;
}


void Button::draw(sf::RenderWindow& win) {
	Entity::draw(win);
	win.draw(text);	
}


sf::Color Button::baseColor = sf::Color(sf::Color::Blue);
sf::Color Button::selectedColor = sf::Color(sf::Color::Cyan);
sf::Color Button::clickedColor = sf::Color(sf::Color(150, 50, 0));