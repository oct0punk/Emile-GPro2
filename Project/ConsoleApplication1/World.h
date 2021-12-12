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
	int eCount = 0;

	World(sf::RenderWindow* win) {
		window = win;
	}

	void PushEntity(Entity* e) {
		data.push_back(e);
		if (e->type == EType::Bot)
			eCount++;
	}

	void update(double dt);
	void draw(sf::RenderWindow& win);

	void KeepEntityOnScreen(Entity* e);
};


