#include "Tuto.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Joystick.hpp"
#include "Tool.hpp"
#include "Command.h"


void Controller::draw(sf::RenderWindow& win, sf::Vector2f pos, sf::RectangleShape& rect, bool animJoystick) {
	if (!Controls::GetInstance()->isConnected)	return;
	joystickAngle += .04f;

	sf::Color initial = rect.getFillColor();
	rect.setFillColor(sf::Color::Red);

	sf::RectangleShape con(controller);
	sf::RectangleShape lJoy(lJoystick);
	sf::RectangleShape rJoy(rJoystick);
	sf::RectangleShape but0(button0);
	sf::RectangleShape aimBut(aimButton);
	sf::RectangleShape shootBut(shootButton);
	rect.setFillColor(initial);

	con.setPosition(pos);
	rJoy.setPosition(pos);
	lJoy.setPosition(pos);
	but0.setPosition(pos);
	shootBut.setPosition(pos);
	aimBut.setPosition(pos);

	if (rJoy.getFillColor() == sf::Color::Red && animJoystick) { 
		sf::Vector2f angleOffset = 
			Magnitude(AimingJoystick()) > 10 ? AimingJoystick() :
			sf::Vector2f(cos(joystickAngle) * 100, sin(joystickAngle) * 100);

		angleOffset.x /= 8;
		angleOffset.y /= 8;
		rJoy.setPosition(pos + angleOffset);
	}
	if (lJoy.getFillColor() == sf::Color::Red && animJoystick) {
		sf::Vector2f lAngle(
			sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X),
			sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y));

		sf::Vector2f angleOffset =
			Magnitude(lAngle) > 10 ? lAngle :
			sf::Vector2f(cos(joystickAngle) * 100, sin(joystickAngle) * 100);
		
		angleOffset.x /= 8;
		angleOffset.y /= 8;
		lJoy.setPosition(pos + angleOffset);
		
	}

	win.draw(con);
	win.draw(lJoy);
	win.draw(rJoy);
	win.draw(but0);
	win.draw(aimBut);
	win.draw(shootBut);
}