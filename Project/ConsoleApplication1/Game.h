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
	GameState state = GameState::Menu;

public:
	PlayerPad* player = nullptr;
	World* world = nullptr;
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

	void ChangeState(GameState nState) {
		state = nState;
		switch (state)
		{
		case Playing:
			world->ImguiWindow = nullptr;
			break;
		case Menu:
			world->selectedButton = world->dataMenu[0];
			world->ImguiWindow = &World::ShowTools;
			break;
		case Pause:
			break;
		case GameOver:
			world->selectedButton = world->dataGameOver[0];
			break;
		default:
			break;
		}
	}
	GameState GetGameState() {
		return state;
	}

	void update(double dt);
	void draw(sf::RenderWindow& win);
	void NextWave();
	int EnemyHealth() { return -1 + wave * 2 + rand() % wave; }

	void Reset();
};

