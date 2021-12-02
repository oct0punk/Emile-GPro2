#pragma once
#include <vector>
#include "Entity.h"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Audio {
public:
	Audio();
};

class World {
public:
	int winW = 1240;
	int winH = 720;
	int gridSize = 8;

	Audio* audio = nullptr;
	std::vector<Entity*>	data;

	void update(double dt);
	void draw(sf::RenderWindow& win);

	std::vector<Particle*> particles;
};

