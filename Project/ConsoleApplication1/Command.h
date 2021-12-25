#pragma once
#include "SFML/Window/Joystick.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Tool.hpp"
#include "Game.h"

bool JoystickIsConnected();

void JoystickShoot();

void MouseShoot();

class Controls {
public:
	bool isConnected = false;
	void (*shoot)() = MouseShoot;

	void Update() {
		if (isConnected != JoystickIsConnected()) {
			isConnected = JoystickIsConnected;
			shoot = isConnected ?
				JoystickShoot :
				MouseShoot;
		}
		shoot();
	}
};