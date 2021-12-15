#pragma once
#include "World.h"

class Game {
private:
	int wave = 0;
	float time = 0.0f;
	float timelaps = 0.0f;
public:
	int enemyCount = 0;

	World* world = nullptr;

	Game(World* w) {
		world = w;
	}

	void update(double dt) {
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
		
		} else {
			if (timelaps > 0) {
				timelaps -= dt;
				if (timelaps <= 0)
					NextWave();
			}
			else if (world->eCount < 1) {
				timelaps = 2.2f;
			}
		}
	}

	void NextWave() {
		wave++;
		enemyCount = wave * 3;
	}
};