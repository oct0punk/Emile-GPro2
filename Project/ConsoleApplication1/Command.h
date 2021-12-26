#pragma once
#include "SFML/Window/Joystick.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Tool.hpp"
#include "Game.h"
#include <iostream>
#include <SFML/Window/Keyboard.hpp>

bool JoystickIsConnected();

sf::Vector2f MoveJoystick();

sf::Vector2f MoveMouse();

sf::Vector2f AimingJoystick();

sf::Vector2f AimingMouse();

bool ShootJoystick();

bool ShootMouse();

class Controls {
public:
	bool isConnected = false;
	sf::Vector2f (*aimingControl)() = AimingMouse;
	sf::Vector2f (*moveControl)() = MoveMouse;
	bool (*shootControl)() = ShootMouse;

	void Update() {
		if (isConnected != JoystickIsConnected()) {
			isConnected = JoystickIsConnected;
			std::cout << isConnected;
			aimingControl = isConnected ?
				AimingJoystick :
				AimingMouse;
			shootControl = isConnected ?
				ShootJoystick :
				ShootMouse;
			moveControl = isConnected ?
				MoveJoystick:
				MoveMouse;
		}
	}
};