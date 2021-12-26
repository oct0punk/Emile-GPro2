#include "Command.h"

bool JoystickIsConnected() {
	return sf::Joystick::isConnected(0);
}

sf::Vector2f MoveJoystick() {
	sf::Vector2f dir(
		sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X),
		sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y)
	);

	if (Magnitude(dir) > 10.0f)
		Normalize(&dir);
	else
		return sf::Vector2f(.0f, .0f);
	return dir;
}

sf::Vector2f MoveMouse() {
	sf::Vector2f pPos;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		pPos.y--;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		pPos.y++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		pPos.x--;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		pPos.x++;
	}
	return pPos;
}

sf::Vector2f AimingJoystick() {
	sf::Vector2f aimDir = sf::Vector2f(
		sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::U),
		sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::V));
	if (Magnitude(aimDir) > 10.0f)
		Normalize(&aimDir);
	else
		return sf::Vector2f(
			cos(Game::GetInstance()->player->getRotation() * DegToRad()),
			sin(Game::GetInstance()->player->getRotation() * DegToRad()));
	return aimDir;
}

sf::Vector2f AimingMouse() {
	PlayerPad* p = Game::GetInstance()->player;
	sf::Vector2f aimDir = sf::Vector2f(
		sf::Mouse::getPosition(*Game::GetInstance()->world->window).x - p->getPosition().x,
		sf::Mouse::getPosition(*Game::GetInstance()->world->window).y - p->getPosition().y);
	Normalize(&aimDir);
	return aimDir;
}

bool ShootJoystick() {
	return sf::Joystick::isButtonPressed(0, 5);
}

bool ShootMouse() {
	return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}
