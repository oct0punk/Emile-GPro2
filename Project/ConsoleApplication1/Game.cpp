#include "Game.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"

Game::Game(World* w) {
	world = w;
}

void Game::update(double dt) {
	switch (state) {
	case Playing:
		world->update(dt);
		if (enemyCount > 0) {
			if (time > 0) {
				time -= dt;
			}
			else {
				time = 0.3f + static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				world->SpawnEnemy(sf::Vector2f(rand() % 1000, rand() % 100));
				enemyCount--;
			}

		}
		else {
			if (world->eCount < 1)
				NextWave();
		}
		break;
	case MainMenu:
		break;
	case Pause:
		break;
	default:
		break;
	}
}

void Game::draw(sf::RenderWindow& win) {
	switch (state)
	{
	case Playing:
		world->draw(win);
		break;
	case MainMenu:
		world->clear(win);
		break;
	case Pause:
		world->draw(win);
		break;
	default:
		break;
	}
}


void Game::NextWave() {
	wave++;
	enemyCount = wave * 3;
}

Game* Game::Instance = nullptr;

//void Button(sf::RenderWindow& win, sf::String str, sf::Vector2f position, sf::Color buttonColor) {
//	sf::Font font;
//	font.loadFromFile("res/arial.ttf");
//
//	sf::Text text(str, font);
//	text.setFillColor(sf::Color::Black);
//	text.setCharacterSize(50);
//	text.setOrigin(text.getCharacterSize() * str.getSize() / 4, text.getCharacterSize()/2);
//
//	float x = 1.6f * str.getSize() * text.getCharacterSize();
//	float y = 1.6f * text.getCharacterSize();
//	sf::RectangleShape rect(sf::Vector2f(x,y));
//	rect.setFillColor(buttonColor);
//	rect.setOutlineThickness(6);
//	rect.setOutlineColor(sf::Color::Black);
//	rect.setOrigin(x/2, y/2);
//
//	rect.setPosition(position);
//	text.setPosition(position);
//
//	win.draw(rect);
//	win.draw(text);
//}
