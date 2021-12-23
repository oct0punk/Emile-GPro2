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
	std::vector<Particle*>	dataFX;
	std::vector<Button*>	dataPause;
	std::vector<Button*>	dataMenu;
	std::vector<Button*>	dataGameOver;
	sf::Color* clearColor = new sf::Color(0, 0, 20, 0);
	float timeScale = 1.0f;
	int eCount = 0;
	bool pauseKeyUp = true;

	World(sf::RenderWindow* win) {
		window = win;

		sf::RectangleShape* rect = new sf::RectangleShape(sf::Vector2f(300, 100));
		rect->setOrigin(150, 50);
		rect->setFillColor(sf::Color(155, 25, 0));

		// Create Buttons
		sf::Font* font = new sf::Font();
		font->loadFromFile("res/arial.ttf");
		sf::Text* text = new sf::Text("Play", *font);

#pragma region Buttons
		Button* menuPlay = new Button(rect, text, PlayMode);
		menuPlay->setPosition(450, 666);
		dataMenu.push_back(menuPlay);

		text->setString("Retry");
		Button* retry = new Button(rect, text, RetryButton);
		retry->setPosition(450, 666);
		dataGameOver.push_back(retry);

#pragma endregion

		for (int i = 0; i < 1000; i++) {
			sf::CircleShape shape(rand() % 100 / 100.0f);
			shape.setFillColor(sf::Color(255 - rand() % 25, 255 - rand() % 10, 255));
			shape.setPosition(rand() % window->getSize().x, rand() % window->getSize().y);
			dataFX.push_back(new Particle(EType::FX, new sf::CircleShape(shape)));
		}
	}

	void PushFX(Particle* p);
	void PushEntity(Entity* e, sf::Vector2f pos = sf::Vector2f(0, 0));
	void SpawnEnemy(sf::Vector2f pos = sf::Vector2f(0, 0));
	void SpawnObstacle(int radius, sf::Vector2f pos);
	void InstantiatePower();

	void updateGame(double dt);
	void updateMenu(double dt);
	void updatePause(double dt);
	void updateGameOver(double dt);
	
	
	void clear(sf::RenderWindow& win) { win.clear(*clearColor); }
	void drawGame(sf::RenderWindow& win);
	void drawMenu(sf::RenderWindow& win);
	void drawGameOver(sf::RenderWindow& win);

	void KeepEntityOnScreen(Entity* e, float value = 50.0f);
};