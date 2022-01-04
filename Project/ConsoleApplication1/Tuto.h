#pragma once
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

class Tuto {
public:
	sf::RectangleShape controller;
	sf::RectangleShape lJoystick;
	sf::RectangleShape rJoystick;
	sf::RectangleShape button0;

	Tuto() {
		sf::Texture conText;
		conText.loadFromFile("res/controller.png");
		conText.setSmooth(true);
		controller.setSize(sf::Vector2f(300, 200));
		controller.setTexture(new sf::Texture(conText));
		controller.setOrigin(400, 0);
		controller.setScale(.3f, .3f);

		sf::Texture lJoysText;
		lJoysText.loadFromFile("res/Ljoystick.png");
		lJoysText.setSmooth(true);
		lJoystick.setSize(sf::Vector2f(300, 200));
		lJoystick.setTexture(new sf::Texture(lJoysText));
		lJoystick.setOrigin(400, 0);
		lJoystick.setScale(.3f, .3f);
		lJoystick.setFillColor(sf::Color::Red);

		sf::Texture rJoysText;
		rJoysText.loadFromFile("res/Rjoystick.png");
		rJoysText.setSmooth(true);
		rJoystick.setSize(sf::Vector2f(300, 200));
		rJoystick.setTexture(new sf::Texture(rJoysText));
		rJoystick.setOrigin(400, 0);
		rJoystick.setScale(.3f, .3f);
		rJoystick.setFillColor(sf::Color::Red);

		sf::Texture butText;
		butText.loadFromFile("res/button0.png");
		butText.setSmooth(true);
		button0.setSize(sf::Vector2f(300, 200));
		button0.setTexture(new sf::Texture(butText));
		button0.setOrigin(400, 0);
		button0.setScale(.3f, .3f);
		button0.setFillColor(sf::Color::Red);
	}


	void setPosition(sf::Vector2f vec)
	{
		controller.setPosition(vec);
		lJoystick.setPosition(vec);
		rJoystick.setPosition(vec);
		button0.setPosition(vec);
	}
};