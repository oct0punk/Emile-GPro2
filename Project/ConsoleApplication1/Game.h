#pragma once
#include "Entity.h"
#include "World.h"
#include "SFML/Graphics/RenderWindow.hpp"

class Game {
public:
	World* world = nullptr;
	PlayerPad* player = nullptr;

	Game(World* w, PlayerPad* p) {
		world = w;
		player = p;
	}

	// ReadFileAndSpawnEntiies()
};