#pragma once
#include <vector>
#include "Entity.h"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/ConvexShape.hpp"

class World {
public:
	
	sf::RenderWindow* window = nullptr;;
	std::vector<Entity*>	dataPlay;
	std::vector<Entity*>	dataPause;
	std::vector<Entity*>	dataMenu;
	sf::Color* clearColor;
	
	int eCount = 0;

	World(sf::RenderWindow* win) {
		window = win;

		sf::RectangleShape* rect = new sf::RectangleShape(sf::Vector2f(300, 100));
		rect->setOrigin(150, 50);
		rect->setFillColor(sf::Color(155, 25, 0));

		sf::Font* font = new sf::Font();
		font->loadFromFile("res/arial.ttf");
		sf::Text* text = new sf::Text("Play", *font);
		Button* button = new Button(rect, text);
		button->setPosition(450, 666);
		dataPlay.push_back(button);

	}


	void PushEntity(Entity* e, sf::Vector2f pos = sf::Vector2f(0, 0));
	void SpawnEnemy(sf::Vector2f pos = sf::Vector2f(0, 0));
	void SpawnObstacle(int radius);

	void update(double dt);
	void clear(sf::RenderWindow& win) {
		win.clear(*clearColor);
	}
	void draw(sf::RenderWindow& win);

	void KeepEntityOnScreen(Entity* e, float value = 10.0f);
};


