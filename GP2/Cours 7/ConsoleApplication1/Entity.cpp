#include "Entity.h"
#include "Tool.hpp"

void Entity::update(double dt) {
	if (isColliding(cx, cy)) {
		float x = clamp(getPosition().x, 0,  1220);
		float y = clamp(getPosition().y, 0, 700);
		setPosition(x, y);
	}
	else
		if (simulated)
			dy += 9.81f * dt;

	setPosition(getPosition().x + dx, getPosition().y + dy);
}

void Entity::draw(sf::RenderWindow& win) {
	if (visible) {
		win.draw(*spr);
	}
}

bool Entity::isColliding(int _cx, int _cy) {
	if (_cx < 0) {
		dx = 0;
		return true;
	}
	if (_cy < 0) {
		dy = 0;
		return true;
	}
	if (_cx > 1190 / *gridSize ) {
		dx = 0;
		return true;
	}
	if (_cy > 670 / *gridSize) {
		dy = 0;
		return true;
	}

	return false;
}

bool Entity::CollisionWithWorld(std::vector<sf::Vector2f> vecs) {
	for (auto v : vecs) {
		if (cx + 3 == v.x && cy == v.y)
			if (rx > * gridSize * 0.7f) {
				rx = 0;
				dx = 0;
				return true;
			}

		if (cy + 3 == v.y && cx == v.x)
			if (ry > * gridSize * 0.7f) {
				ry = 0;
				dy = 0;
				return true;
			}

		if (cx - 1 == v.x && cy == v.y)
			if (rx < *gridSize * 0.3f) {
				rx = *gridSize;
				dx = 0;
				return true;
			}

		if (cy - 1 == v.y && cx == v.x)
			if (ry < *gridSize * 0.3f) {
				setPosition(getPosition().x, getPosition().y + 1);
				ry = *gridSize;
				dy = 0;
				return true;
			}

	}
	return false;
}

void PlayerPad::update(double dt) {

}

void PlayerPad::draw(sf::RenderWindow& win) {
	if (visible)
		win.draw(*spr);

}
