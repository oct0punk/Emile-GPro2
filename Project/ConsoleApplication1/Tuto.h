#pragma once
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"


struct Controller {
	float joystickAngle = 0;

	sf::RectangleShape controller;
	sf::RectangleShape lJoystick;
	sf::RectangleShape rJoystick;
	sf::RectangleShape button0;
	sf::RectangleShape aimButton;
	sf::RectangleShape shootButton;

	
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
		lJoystick.setFillColor(sf::Color::Transparent);

		sf::Texture rJoysText;
		rJoysText.loadFromFile("res/Rjoystick.png");
		rJoysText.setSmooth(true);
		rJoystick.setSize(sf::Vector2f(300, 200));
		rJoystick.setTexture(new sf::Texture(rJoysText));
		rJoystick.setOrigin(400, 0);
		rJoystick.setScale(.6f, .6f);
		rJoystick.setFillColor(sf::Color::Transparent);

		sf::Texture butText;
		butText.loadFromFile("res/button0.png");
		butText.setSmooth(true);
		button0.setSize(sf::Vector2f(300, 200));
		button0.setTexture(new sf::Texture(butText));
		button0.setOrigin(400, 0);
		button0.setScale(.6f, .6f);

		sf::Texture aimButText;
		aimButText.loadFromFile("res/AimButton.png");
		aimButText.setSmooth(true);
		aimButton.setSize(sf::Vector2f(300, 200));
		aimButton.setTexture(new sf::Texture(aimButText));
		aimButton.setOrigin(400, 0);
		aimButton.setScale(.6f, .6f);
		aimButton.setFillColor(sf::Color::Transparent);

		sf::Texture shootButText;
		shootButText.loadFromFile("res/ShootButton.png");
		shootButText.setSmooth(true);
		shootButton.setSize(sf::Vector2f(300, 200));
		shootButton.setTexture(new sf::Texture(shootButText));
		shootButton.setOrigin(400, 0);
		shootButton.setScale(.6f, .6f);
		shootButton.setFillColor(sf::Color::Transparent);
	}


	void setPosition(sf::Vector2f vec)
	{
		controller.setPosition(vec);
		lJoystick.setPosition(vec);
		rJoystick.setPosition(vec);
		button0.setPosition(vec);
		aimButton.setPosition(vec);
		shootButton.setPosition(vec);
	}

	// Draw a controller.
	// rect parameter color a RectangleShape, please write controller's class button
	void draw(sf::RenderWindow& win, sf::Vector2f pos, sf::RectangleShape& rect, bool animJoystick = false);
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

	void DrawRJoystick(sf::RenderWindow& win, sf::Vector2f pos, bool anim = false) {
		controller->draw(win, pos, controller->rJoystick, anim);
	}

	void DrawLJoystick(sf::RenderWindow& win, sf::Vector2f pos, bool anim = false) {
		controller->draw(win, pos, controller->lJoystick, anim);
	}

	void DrawAimButton(sf::RenderWindow& win, sf::Vector2f pos) {
		controller->draw(win, pos, controller->aimButton);
	}

	void DrawShootButton(sf::RenderWindow& win, sf::Vector2f pos) {
		controller->draw(win, pos, controller->shootButton);
	}
};