#include "Entity.h"

void Entity::update(double dt) {
	sf::Vector2f move = getPosition();
	move.x += dx * dt;
	move.y += dy * dt;
	setPosition(move.x, move.y);

}

void Entity::draw(sf::RenderWindow& win) {
	if (visible) 
		win.draw(*spr);
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
	float dx = _dx * 1000.0f;
	float dy = _dy * 1000.0f;
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

void Laser::update(double dt) {
	if (reloading > 0.0f) {
		reloading -= dt;
	}
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
