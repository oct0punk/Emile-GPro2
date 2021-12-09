#include "Entity.h"
#include "Tool.hpp"

void Entity::update(double dt) {
	if (isColliding(cx, cy)) {
		float x = clamp(getPosition().x, 0,  1190);
		float y = clamp(getPosition().y, 0, 670);
		setPosition(x, y);
	}
}

void Entity::draw(sf::RenderWindow& win) {
	if (visible) {
		win.draw(*spr);
	}
}

bool Entity::isColliding(int _cx, int _cy) {
	if (_cx < 0)
		return true;
	if (_cy < 0)
		return true;
	if (_cx > *gridSize - 1)
		return true;
	if (_cy > *gridSize - 1)
		return true;

	return false;
}

void Entity::CollisionWithWorld(std::vector<sf::Vector2f> vecs) {
	for (auto v : vecs) {
		if (cx + 3 == v.x && cy == v.y)
			if (rx > * gridSize * 0.7f) {
				setPosition(getPosition().x - *gridSize * 0.1f, getPosition().y);
			}

		if (cy + 3 == v.y && cx == v.x)
			if (ry > * gridSize * 0.7f) {
				setPosition(getPosition().x, getPosition().y - *gridSize * 0.1f);
			}

		if (cx - 1 == v.x && cy == v.y)
			if (rx < *gridSize * 0.3f) {
				setPosition(getPosition().x + *gridSize * 0.1f, getPosition().y);
			}

		if (cy - 1 == v.y && cx == v.x)
			if (ry < *gridSize * 0.3f) {
				setPosition(getPosition().x, getPosition().y + *gridSize * 0.1f);
			}

	}

}

void PlayerPad::update(double dt) {

}

void PlayerPad::draw(sf::RenderWindow& win) {
	if (visible)
		win.draw(*spr);

}
