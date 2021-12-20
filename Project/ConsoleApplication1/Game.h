#pragma once
#include "World.h"

enum  GameState {
	Playing,
	Menu,
	Pause,
	GameOver
};

class Game {
private:
	static Game* Instance;
	
	float time = 0.0f;

public:
	int wave = 0;
	PlayerPad* player = nullptr;
	World* world = nullptr;
	int enemyCount = 5;
	GameState state = GameState::Menu;

	static void create(World* w, PlayerPad* p) {
		Instance = new Game(w);
		Instance->player = p;
	}

	static Game* GetInstance() {
		return Instance;
	}

	Game(World* w);

	void update(double dt);
	void draw(sf::RenderWindow& win);
	void NextWave();
	int EnemyHealth() { return wave * 3; }

	void Reset() {
		world->DestroyAllEnemies();		
		player->Revive();
		state = GameState::Playing;
		wave = 0;
		NextWave();
	}
};

