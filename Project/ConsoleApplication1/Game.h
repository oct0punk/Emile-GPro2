#pragma once
#include "Entity.h"
#include "World.h"
#include "SFML/Graphics/RenderWindow.hpp"

class Game {
public:
	const Game* Instance = nullptr;
	World* world = nullptr;
	PlayerPad* player = nullptr;

	Game(World* w, PlayerPad* p) {
		Instance = this;
		world = w;
		player = p;
	}

	void Spawn(Entity e, World& world) {

	}

	// ReadFileAndSpawnEntiies()
};