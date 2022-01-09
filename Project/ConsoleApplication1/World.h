#pragma once
#include <vector>
#include "Entity.h"
#include "Tuto.h"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/ConvexShape.hpp"
#include "imgui.h"
#include "imgui-SFML.h"


class World {
	bool aimDisplay = true;

public:
	Button* selectedButton = nullptr;
	sf::RenderWindow* window = nullptr;
	Tuto* tuto;
	sf::CircleShape* cursor = nullptr;

	std::vector<Entity*>	dataPlay;
	std::vector<Particle*>	dataFX;
	std::vector<Button*>	dataPause;
	std::vector<Button*>	dataMenu;
	std::vector<Button*>	dataGameOver;
	sf::Text credit;
	sf::Text* scoretxt = nullptr;

	sf::Color* clearColor = new sf::Color(0, 0, 20, 0);
	void (World::* ImguiWindow)() = &World::ShowTools;

	float timeSinceLevelLoad = 0.0f;
	float timeScale = 1.0f;
	int eCount = 0;
	bool pauseKeyUp = true;
	float flashTime = 0.0f;

	World(sf::RenderWindow* win) {
		Enemy::oColor = sf::Color::Blue;
		tuto = new Tuto();
		window = win;

		// Used for buttons
		sf::Font* font = new sf::Font();
		font->loadFromFile("res/astro.ttf");
		sf::Text* text = new sf::Text("Play", *font);

		sf::RectangleShape* rect = new sf::RectangleShape(
			sf::Vector2f(
				text->getString().getSize() * text->getCharacterSize() * 1.32f,
				text->getCharacterSize() * 2.3f));
		rect->setOrigin(20, 20);
		rect->setFillColor(sf::Color(155, 25, 0));


	#pragma region Button
		// --------------------------- PLAY BUTTON ---------------------------
		Button* menuPlay = new Button(rect, text, PlayMode);
		menuPlay->setPosition(450, 666);
		dataMenu.push_back(menuPlay);
		

		// --------------------------- OPTIONS BUTTON ---------------------------
		text->setString("Options");
		rect = new sf::RectangleShape(
			sf::Vector2f(
				text->getString().getSize() * text->getCharacterSize() * 1.24f,
				text->getCharacterSize() * 2.3f));
		rect->setOrigin(20, 20);
		Button* options = new Button(rect, text, OptionButton);
		options->setPosition(750, 666);
		dataMenu.push_back(options);

		// --------------------------- RETRY BUTTON ---------------------------
		text->setString("Retry");
		rect = new sf::RectangleShape(
			sf::Vector2f(
				text->getString().getSize() * text->getCharacterSize() * 1.24f,
				text->getCharacterSize() * 2.3f));
		Button* retry = new Button(rect, text, PlayMode);
		retry->setPosition(450, 666);
		dataGameOver.push_back(retry);

		// --------------------------- MAIN MENU BUTTON ---------------------------
		text->setString("Main Menu");
		rect = new sf::RectangleShape(
			sf::Vector2f(
				text->getString().getSize() * text->getCharacterSize() * 1.24f,
				text->getCharacterSize() * 2.3f));
		Button* menuButton = new Button(rect, text, BackToMenu);
		menuButton->setPosition(750, 666);
		dataGameOver.push_back(menuButton);
#pragma endregion


	#pragma region Credit

		// Print credit text written in "res/credit.txt"
		FILE* f = nullptr;
		fopen_s(&f, "res/credit.txt", "rb");
		char* str = nullptr;
		long size = 0;
		fseek(f, 0, SEEK_END);
		size = ftell(f);
		rewind(f);
		str = (char*)malloc(sizeof(char) * size);
		fread(str, 1, size, f);
		str[strlen(str) - 4] = 0;
		fclose(f);

		credit.setFont(*font);
		credit.setString(sf::String(str));
		credit.setCharacterSize(12);
		credit.setPosition(10, 10);

#pragma endregion

		// Stars in background
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
	void KeepEntityOnScreen(Entity* e, float value = 50.0f);

	void updateGame(double dt);
	void updateMenu(double dt);
	void updatePause(double dt);
	void updateGameOver(double dt);

	void clear(sf::RenderWindow& win) { win.clear(*clearColor); }
	void drawGame(sf::RenderWindow& win);
	void drawMenu(sf::RenderWindow& win);
	void drawGameOver(sf::RenderWindow& win);

	void ShowTools();
	void ColorsTool();
};
