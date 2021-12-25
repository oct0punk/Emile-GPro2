#include "Command.h"

bool JoystickIsConnected() {
	return sf::Joystick::isConnected(0);
}

void JoystickShoot() {
	sf::Vector2f aimDir = sf::Vector2f(
		sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::U),
		sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::V));
	Normalize(&aimDir);
	PlayerPad* p = Game::GetInstance()->player;
	float angle = atan2(aimDir.y, aimDir.x) * RadToDeg();
	p->setRotation(angle);
	// p->laser->create(p->getPosition().x, p->getPosition().y, aimDir.x, aimDir.y);
}

void MouseShoot() {
	PlayerPad* p = Game::GetInstance()->player;
	sf::Vector2f aimDir = sf::Vector2f(
		sf::Mouse::getPosition(*Game::GetInstance()->world->window).x - p->getPosition().x,
		sf::Mouse::getPosition(*Game::GetInstance()->world->window).y - p->getPosition().y);
	Normalize(&aimDir);
	float angle = atan2(aimDir.y, aimDir.x) * RadToDeg();
	p->setRotation(angle);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		p->laser->create(p->getPosition().x, p->getPosition().y, aimDir.x, aimDir.y, .067f);
}
