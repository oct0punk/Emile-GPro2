#include "Entity.h"

void Entity::update(double dt) {
	sf::Vector2f move = getPosition();
	move.x += dx * dt;
	move.y += dy * dt;
	setPosition(move.x, move.y);

}

void Entity::draw(sf::RenderWindow& win) {
	if (visible) {
		if (spr->getOutlineColor() == sf::Color::White)
			visible = false;
		win.draw(*spr);
	}
}

bool Entity::CheckCollision(Entity* wall, Entity* ball) {
	if (wall->spr->getGlobalBounds().contains(ball->getPosition())) {
		float x = ball->getPosition().x - wall->getPosition().x;
		float y = ball->getPosition().y - wall->getPosition().y;
		float magnitude = sqrt(x * x + y * y);
		x /= magnitude;
		y /= magnitude;

		float w = wall->spr->getGlobalBounds().width / 2;
		float h = wall->spr->getGlobalBounds().height / 2;
		magnitude = sqrt(w * w + h * h);
		w /= magnitude;
		h /= magnitude;

		if (abs(x) > w)		ball->dx *= -1;
		else if (abs(y) > h)	ball->dy *= -1;
		ball->spr->setOutlineColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
		wall->spr->setOutlineColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
		ball->setPosition(ball->lastGoodPos.x, ball->lastGoodPos.y);
		return true;
	}
	ball->lastGoodPos = ball->getPosition();
	return false;
}


void PlayerPad::update(double dt) {
}

void PlayerPad::draw(sf::RenderWindow& win) {
	if (visible)
		win.draw(*spr);

}


void Particle::update(double dt) {
	Entity::update(dt);
	dy += 9.81f;

	sf::Color c = spr->getFillColor();
	spr->setFillColor(sf::Color(c.r, c.g, c.b, (timeLeft * 255)));
	spr->setOutlineColor(sf::Color(c.r, c.g, c.b, (timeLeft * 255)));
	
	timeLeft = timeLeft - dt;
	if (timeLeft < 0)
		visible = false;
}

void Particle::draw(sf::RenderWindow& win) {
	if (visible)
		win.draw(*spr);
}


void LaserShot::create(float _px, float _py, float dir) {
	float angle = 90 - dir;
	float dx = cos(angle) * 57.2958f;
	float dy = sin(angle) * 57.2958f;
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

void LaserShot::update(double dt) {
	for (int i = 0; i < px.size(); ++i) {
		if (alive[i]) {		// Move each shape into (dx ; dy)
			px[i] += dx[i] * dt;
			py[i] += dy[i] * dt;
			if (	// Check id f outside screen
				(px[i] > 3000) || (px[i] < -100) ||
				(py[i] > 3000) || (py[i] < -100)
				) {
				alive[i] = false;
			}
		}
	}
}

void LaserShot::draw(sf::RenderWindow& win) {
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
