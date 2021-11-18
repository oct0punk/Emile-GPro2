#pragma once
#include <vector>
#include "Entity.h"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Audio {
public:
	Audio();
	sf::Sound		pong;
	sf::SoundBuffer pongBuffer;
};

class World {
public:
	Audio* audio = nullptr;
	std::vector<Entity*>	data;

	void update(double dt);
	void draw(sf::RenderWindow& win);

	std::vector<Entity> toBreak;
};

