#pragma once
#include <vector>
#include "Entity.h"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/ConvexShape.hpp"

class Audio {
public:
	Audio();
};

class World {
public:
	
	sf::RenderWindow* window = nullptr;;
	std::vector<Entity*>	data;
	sf::Color* clearColor;
	Audio* audio = nullptr;

	int eCount = 0;

	World(sf::RenderWindow* win) {
		window = win;
	}

	void PushEntity(Entity* e, sf::Vector2f pos = sf::Vector2f(0, 0)) {
		bool inserted = false;
		for (auto entity : data) {
			if (entity->type == e->type)
				if (!entity->visible) {
					inserted = true;
					entity->visible = true;
					entity->setPosition(pos.x, pos.y);
					break;
				}
		}
		if (!inserted) data.push_back(e);

		

		if (e->type == EType::Bot) {
			eCount++;
			Enemy* enemy = (Enemy*)e;
			for (auto b : data) {
				if (b->type == Player) {
					enemy->p = (PlayerPad*)b;
					break;
				}
			}
		}
		e->setPosition(pos.x, pos.y);
	}

	void SpawnEnemy(sf::Vector2f pos = sf::Vector2f(0, 0));

	void update(double dt);
	void draw(sf::RenderWindow& win);

	void KeepEntityOnScreen(Entity* e);
};


