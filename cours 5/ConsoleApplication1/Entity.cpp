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
		return true;
	}
	return false;
}

void PlayerPad::update(double dt) {
	CheckCollision(this, currentBall);
}

void PlayerPad::draw(sf::RenderWindow& win) {
	if (visible)
		win.draw(*spr);	

}
