#pragma once
#include "World.h"

class Game {
private:
	int wave = 0;
	float time = 0.0f;
	bool spawned = false;
public:
	int enemyCount = 0;

	World* world = nullptr;

	Game(World* w) {
		world = w;
	}

	void update(double dt) {
		world->update(dt);
		if (enemyCount < 1) return;

		if (time > 0) {
			spawned = false;
			time -= dt;
		} else {
			if (!spawned) {
				time = rand() % 2;
				world->SpawnEnemy(sf::Vector2f(rand() % 1000, rand() % 100));
				enemyCount--;
				spawned = true;
			}
		}
	}
};