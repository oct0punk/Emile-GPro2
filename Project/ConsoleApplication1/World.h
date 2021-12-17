#pragma once
#include <vector>
#include "Entity.h"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/ConvexShape.hpp"

class World {
public:
	
	sf::RenderWindow* window = nullptr;;
	std::vector<Entity*>	data;
	sf::Color* clearColor;
	
	int eCount = 0;

	World(sf::RenderWindow* win) {
		window = win;
	}


	void PushEntity(Entity* e, sf::Vector2f pos = sf::Vector2f(0, 0));
	void SpawnEnemy(sf::Vector2f pos = sf::Vector2f(0, 0));
	void SpawnObstacle(int radius);

	void update(double dt);
	void clear(sf::RenderWindow& win) {
		win.clear(*clearColor);
	}
	void draw(sf::RenderWindow& win);

	void KeepEntityOnScreen(Entity* e, float value = 10.0f);
};


