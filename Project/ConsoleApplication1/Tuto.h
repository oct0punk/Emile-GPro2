#pragma once
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/RectangleShape.hpp"


struct Controller {
	float joystickAngle = 0;

	sf::RectangleShape controller;
	sf::RectangleShape lJoystick;
	sf::RectangleShape rJoystick;
	sf::RectangleShape button0;

	
public:
	Controller() {
		sf::Texture conText;
		conText.loadFromFile("res/controller.png");
		conText.setSmooth(true);
		controller.setSize(sf::Vector2f(300, 200));
		controller.setTexture(new sf::Texture(conText));
		controller.setOrigin(400, 0);
		controller.setScale(.6f, .6f);

		sf::Texture lJoysText;
		lJoysText.loadFromFile("res/Ljoystick.png");
		lJoysText.setSmooth(true);
		lJoystick.setSize(sf::Vector2f(300, 200));
		lJoystick.setTexture(new sf::Texture(lJoysText));
		lJoystick.setOrigin(400, 0);
		lJoystick.setScale(.6f, .6f);

		sf::Texture rJoysText;
		rJoysText.loadFromFile("res/Rjoystick.png");
		rJoysText.setSmooth(true);
		rJoystick.setSize(sf::Vector2f(300, 200));
		rJoystick.setTexture(new sf::Texture(rJoysText));
		rJoystick.setOrigin(400, 0);
		rJoystick.setScale(.6f, .6f);

		sf::Texture butText;
		butText.loadFromFile("res/button0.png");
		butText.setSmooth(true);
		button0.setSize(sf::Vector2f(300, 200));
		button0.setTexture(new sf::Texture(butText));
		button0.setOrigin(400, 0);
		button0.setScale(.6f, .6f);
	}


	void setPosition(sf::Vector2f vec)
	{
		controller.setPosition(vec);
		lJoystick.setPosition(vec);
		rJoystick.setPosition(vec);
		button0.setPosition(vec);
	}

	void draw(sf::RenderWindow& win, sf::Vector2f pos, sf::RectangleShape& rect) {
		joystickAngle+= .1f;

		rect.setFillColor(sf::Color::Red);

		sf::RectangleShape con(controller);
		sf::RectangleShape lJoy(lJoystick);
		sf::RectangleShape rJoy(rJoystick);
		sf::RectangleShape but0(button0);
		
		rect.setFillColor(sf::Color::White);

		con.setPosition(pos);
		float magnitude = 10;
		sf::Vector2f angleOffset(cos(joystickAngle) * magnitude, sin(joystickAngle) * magnitude);
		if (lJoy.getFillColor() == sf::Color::Red) {
			lJoy.setPosition(pos + angleOffset);
			rJoy.setPosition(pos);
		}
		else if (rJoy.getFillColor() == sf::Color::Red) {
			rJoy.setPosition(pos + angleOffset);
			lJoy.setPosition(pos);
		}
		else {
			rJoy.setPosition(pos);
			lJoy.setPosition(pos);
		}
		but0.setPosition(pos);

		win.draw(con);
		win.draw(lJoy);
		win.draw(rJoy);
		win.draw(but0);
	}
};


class Tuto {
	Controller* controller = nullptr;
public:
	

	Tuto() {
		controller = new Controller();
	}

	void DrawController(sf::RenderWindow& win, sf::Vector2f pos) {
		controller->draw(win, pos, *(new sf::RectangleShape()));
	}

	void DrawButton0(sf::RenderWindow& win, sf::Vector2f pos) {
		controller->draw(win, pos, controller->button0);
	}

	void DrawRJoystick(sf::RenderWindow& win, sf::Vector2f pos) {
		controller->draw(win, pos, controller->rJoystick);
	}

	void DrawLJoystick(sf::RenderWindow& win, sf::Vector2f pos) {
		controller->draw(win, pos, controller->lJoystick);
	}
};