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
	PlayerPad* player = nullptr;
	World* world = nullptr;
	GameState state = GameState::Menu;
	int wave = 0;
	int enemyCount = 0;
	bool pHit = false;

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
	int EnemyHealth() { return -1 + wave * 2 + rand() % wave; }

	void Reset();
};

