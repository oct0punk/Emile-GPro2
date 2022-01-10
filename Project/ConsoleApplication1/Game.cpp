#include "Game.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"

Game::Game(World* w) { world = w; }

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
		world->updatePause(dt);
		break;
	case GameOver:
		world->updateGameOver(dt);
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
		world->drawMenu(win);
		break;
	case Pause:
		world->drawGame(win);
		break;
	case GameOver:
		world->drawGameOver(win);
		break;
	default:
		break;
	}
}



void Game::NextWave() {
	wave++;
	enemyCount = wave * 3;
	int radius = 50 + rand() % 50;
	world->SpawnObstacle(radius, sf::Vector2f(-radius, -radius));
	radius = rand() % 100;
	world->SpawnObstacle(radius, sf::Vector2f(-1000, 2000 -radius));

	player->ChangeHealth(1);
	world->InstantiatePower();
	
}

// Launch a game from the beginning
void Game::Reset() {
	for (auto e : world->dataPlay) {	// Disable all elements in world
		if (e->type != Player || e->type != Bullet)
			e->visible = false;
		else
			e->visible = true;
	}
	world->eCount = 0;
	player->Revive();
	ChangeState(GameState::Playing);
	wave = 0;
	score = 0;
	NextWave();
}



Game* Game::Instance = nullptr;