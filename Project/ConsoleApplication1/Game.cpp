#include "Game.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"

Game::Game(World* w) {
	world = w;
}

void Game::update(double dt) {
	switch (state) {
	case Playing:
		world->updateGame(dt);
		if (enemyCount > 0) {
			if (time > 0) {
				time -= dt;
			}
			else {
				time = 0.3f + static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				world->SpawnEnemy(sf::Vector2f(rand() % 1000, - 500 -rand() % 100));
				enemyCount--;
			}

		}
		else {
			if (world->eCount < 1)
				NextWave();
		}
		break;
	case Menu:
		world->updateMenu(dt);
		break;
	case Pause:
		world->updatePause();
		break;
	default:
		break;
	}
}

void Game::draw(sf::RenderWindow& win) {
	switch (state)
	{
	case Playing:
		world->drawGame(win);
		break;
	case Menu:
		world->clear(win);
		world->drawMenu(win);
		break;
	case Pause:
		world->drawGame(win);
		break;
	default:
		break;
	}
}


void Game::NextWave() {
	wave++;
	enemyCount = wave * 3;
	int radius = rand() % 100;
	world->SpawnObstacle(radius, sf::Vector2f(-radius, -radius));
	radius = rand() % 100;
	world->SpawnObstacle(radius, sf::Vector2f(10000, -radius));

	for (auto p : world->dataPlay)
		if (p->type == EType::Player)
		{
			PlayerPad* pad = (PlayerPad*)p;
			pad->ChangeHealth(1);
			return;
		}
}

Game* Game::Instance = nullptr;

