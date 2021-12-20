#pragma once
#include "World.h"

enum GameState {
	Playing,
	Menu,
	Pause,
	GameOver
};

class Game {
private:
	World* world = nullptr;
	static Game* Instance;
	
	int wave = 0;
	float time = 0.0f;

public:
	int enemyCount = 5;
	GameState state = GameState::Menu;

	static void create(World* w) {
		Instance = new Game(w);
	}

	static Game* GetInstance() {
		return Instance;
	}

	Game(World* w);

	void update(double dt);
	void draw(sf::RenderWindow& win);
	void NextWave();
	int EnemyHealth() {
		return wave * 3;
	}
};

