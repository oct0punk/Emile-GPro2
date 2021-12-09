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

	sf::RenderWindow* window = nullptr;;
	sf::Color* clearColor;
	float timeScale = 1.0f;
	Audio* audio = nullptr;
	std::vector<Entity*>	data;

	World(sf::RenderWindow* win) {
		window = win;
	}

	void update(double dt);
	void draw(sf::RenderWindow& win);

	void KeepEntityOnScreen(Entity* e);
};


