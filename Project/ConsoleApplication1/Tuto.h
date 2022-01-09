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

	void draw(sf::RenderWindow& win, sf::Vector2f pos, int animJoystick = 0);
};


class Tuto {
	Controller* controller = nullptr;
	sf::RectangleShape zqsd;
	sf::RectangleShape left;
	sf::RectangleShape space;
	sf::Color color = sf::Color::Red;	// highlight color
public:
	bool powerTuto = true;
	bool shootPowerTuto = true;

	Tuto() {
		controller = new Controller();

		sf::Texture zqsdText;
		zqsdText.loadFromFile("res/zqsd.png");
		zqsdText.setSmooth(true);
		zqsd.setSize(sf::Vector2f(300, 200));
		zqsd.setTexture(new sf::Texture(zqsdText));
		zqsd.setOrigin(400, 0);
		zqsd.setFillColor(sf::Color::Yellow);

		sf::Texture leftText;
		leftText.loadFromFile("res/left.png");
		leftText.setSmooth(true);
		left.setSize(sf::Vector2f(300, 200));
		left.setTexture(new sf::Texture(leftText));
		left.setOrigin(400, 0);
		left.setScale(.6f, .6f);
		left.setFillColor(sf::Color::Yellow);

		sf::Texture spaceText;
		spaceText.loadFromFile("res/space.png");
		spaceText.setSmooth(true);
		space.setSize(sf::Vector2f(300, 200));
		space.setTexture(new sf::Texture(spaceText));
		space.setOrigin(400, 0);
		space.setFillColor(sf::Color::Yellow);
	}


	void DrawController(sf::RenderWindow& win, sf::Vector2f pos);

	void DrawButton0(sf::RenderWindow& win, sf::Vector2f pos);

	void DrawMoveCommand(sf::RenderWindow& win, sf::Vector2f pos);

	void DrawRJoystick(sf::RenderWindow& win, sf::Vector2f pos);

	void DrawPower(sf::RenderWindow& win, sf::Vector2f pos);

	void DrawAimButton(sf::RenderWindow& win, sf::Vector2f pos);

	void DrawShootButton(sf::RenderWindow& win, sf::Vector2f pos);
};