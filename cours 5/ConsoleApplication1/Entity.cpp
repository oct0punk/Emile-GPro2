#include "Entity.h"

void Entity::update(double dt) {
	sf::Vector2f move = getPosition();
	move.x += dx * dt;
	move.y += dy * dt;
	setPosition(move.x, move.y);
}

void Entity::draw(sf::RenderWindow& win) {
	if (spr)
		win.draw(*spr);
}

void PlayerPad::update(double dt) {

}

void PlayerPad::draw(sf::RenderWindow& win) {
	if (spr)
		win.draw(*spr);
}
