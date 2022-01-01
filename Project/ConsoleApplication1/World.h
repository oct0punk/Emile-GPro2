#pragma once
#include <vector>
#include "Entity.h"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/ConvexShape.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

class World {
public:	
	Button* selectedButton = nullptr;
	sf::RenderWindow* window = nullptr;

	std::vector<Entity*>	dataPlay;
	std::vector<Particle*>	dataFX;
	std::vector<Button*>	dataPause;
	std::vector<Button*>	dataMenu;
	std::vector<Button*>	dataGameOver;
	sf::Text credit;

	sf::Color* clearColor = new sf::Color(0, 0, 20, 0);
	void (World::* ImguiWindow)() = &World::ShowTools;

	float timeScale = 1.0f;
	int eCount = 0;
	bool pauseKeyUp = true;

	World(sf::RenderWindow* win) {
		window = win;
		// Create Buttons

		sf::Font* font = new sf::Font();
		font->loadFromFile("res/astro.ttf");
		sf::Text* text = new sf::Text("Play", *font);

		sf::RectangleShape* rect = new sf::RectangleShape(
			sf::Vector2f(
				text->getString().getSize() * text->getCharacterSize() * 1.32f,
				text->getCharacterSize() * 2.3f));
		rect->setOrigin(20, 20);
		rect->setFillColor(sf::Color(155, 25, 0));

		#pragma region UI
		Button* menuPlay = new Button(rect, text, PlayMode);
		menuPlay->setPosition(450, 666);
		dataMenu.push_back(menuPlay);
		selectedButton = menuPlay;

		text->setString("Retry");
		rect = new sf::RectangleShape(
			sf::Vector2f(
				text->getString().getSize() * text->getCharacterSize() * 1.24f,
				text->getCharacterSize() * 2.3f));
		rect->setOrigin(20, 20);
		Button* retry = new Button(rect, text, RetryButton);
		retry->setPosition(450, 666);
		dataGameOver.push_back(retry);

		FILE* f;
		fopen_s(&f, "res/credit.txt", "rb");
		char* str;
		long size;
		fseek(f, 0, SEEK_END);
		size = ftell(f);
		rewind(f);
		str = (char*)malloc(sizeof(char) * size);
		fread(str, 1, size, f);
		str[strlen(str) - 4] = 0;
		fclose(f);


		credit.setFont(*font);
		credit.setString(sf::String(str));
		credit.setPosition(666, 100);
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

	void ShowTools() {
		using namespace ImGui;
		Begin("Edit");
		float col[4] {clearColor->r, clearColor->g, clearColor->b, clearColor->a};
		//if (SliderFloat4("color", col, 0.0f, 255.0f)) {
		//	clearColor->r = col[0];
		//	clearColor->g = col[1];
		//	clearColor->b = col[2];
		//}
		if (ColorEdit3("Color", col)) {
			clearColor->r = col[0] * 255.0f;
			clearColor->g = col[1] * 255.0f;
			clearColor->b = col[2] * 255.0f;
		}
		Value("r", clearColor->r);
		Value("g", clearColor->g);
		Value("b", clearColor->b);
		Value("a", clearColor->a);
		End();
	}
};
