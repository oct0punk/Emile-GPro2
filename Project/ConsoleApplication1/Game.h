#pragma once
#include "World.h"

enum GameState {
	Playing,
	MainMenu,
	Pause
};

class Game {
private:
	World* world = nullptr;
	static Game* Instance;
	GameState state = GameState::Playing;
	
	int wave = 0;
	float time = 0.0f;
	int enemyCount = 5;

public:
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
};

//
//void Button(sf::RenderWindow& win, sf::String str, sf::Vector2f position, sf::Color buttonColor = sf::Color::White);