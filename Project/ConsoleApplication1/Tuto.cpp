#include "Tuto.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Joystick.hpp"
#include "Tool.hpp"
#include "Command.h"


void Controller::draw(sf::RenderWindow& win, sf::Vector2f pos, int animJoystick) {
	joystickAngle += .04f;


	setPosition(pos);

	if (animJoystick == 1) {
		sf::Vector2f lAngle(
			sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X),
			sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y));

		sf::Vector2f angleOffset =
			Magnitude(lAngle) > 10 ? lAngle :
			sf::Vector2f(cos(joystickAngle) * 100, sin(joystickAngle) * 100);

		angleOffset.x /= 8;
		angleOffset.y /= 8;
		lJoystick.setPosition(pos + angleOffset);

	}
	if (animJoystick == 2) {
		sf::Vector2f angleOffset =
			Magnitude(AimingJoystick()) > 10 ? AimingJoystick() :
			sf::Vector2f(cos(joystickAngle) * 100, sin(joystickAngle) * 100);

		angleOffset.x /= 8;
		angleOffset.y /= 8;
		rJoystick.setPosition(pos + angleOffset);
	}

	win.draw(controller);
	win.draw(lJoystick);
	win.draw(rJoystick);
	win.draw(button0);
	win.draw(aimButton);
	win.draw(shootButton);
}


void Tuto::DrawController(sf::RenderWindow& win, sf::Vector2f pos) {
	controller->controller.setFillColor(color);
	controller->draw(win, pos);
	controller->controller.setFillColor(sf::Color::White);
}

void Tuto::DrawButton0(sf::RenderWindow& win, sf::Vector2f pos) {
	if (!Controls::GetInstance()->isConnected) return;
	controller->button0.setFillColor(color);
	controller->draw(win, pos);
	controller->button0.setFillColor(sf::Color::White);
}

void Tuto::DrawMoveCommand(sf::RenderWindow& win, sf::Vector2f pos) {
	if (Controls::GetInstance()->isConnected) {
		controller->lJoystick.setFillColor(color);
		controller->draw(win, pos, 1);
		controller->lJoystick.setFillColor(sf::Color::Transparent);
		return;
	}
	zqsd.setPosition(pos);
	win.draw(zqsd);
}

void Tuto::DrawRJoystick(sf::RenderWindow& win, sf::Vector2f pos) {
	if (!Controls::GetInstance()->isConnected) return;
	controller->rJoystick.setFillColor(color);
	controller->draw(win, pos, 2);
	controller->rJoystick.setFillColor(sf::Color::Transparent);
}

void Tuto::DrawPower(sf::RenderWindow& win, sf::Vector2f pos) {
	if (Controls::GetInstance()->isConnected) {
		controller->lJoystick.setFillColor(color);
		controller->draw(win, pos, 0);
		controller->lJoystick.setFillColor(sf::Color::Transparent);
		controller->rJoystick.setFillColor(color);
		controller->draw(win, pos, 0);
		controller->rJoystick.setFillColor(sf::Color::Transparent);
		return;
	}
	space.setPosition(pos);
	win.draw(space);
}

void Tuto::DrawAimButton(sf::RenderWindow& win, sf::Vector2f pos) {
	if (!Controls::GetInstance()->isConnected) return;
	controller->aimButton.setFillColor(color);
	controller->draw(win, pos);
	controller->aimButton.setFillColor(sf::Color::White);
}

void Tuto::DrawShootButton(sf::RenderWindow& win, sf::Vector2f pos) {
	if (Controls::GetInstance()->isConnected) {
		controller->shootButton.setFillColor(color);
		controller->draw(win, pos);
		controller->shootButton.setFillColor(sf::Color::White);
		return;
	}
	left.setPosition(pos);
	win.draw(left);
}