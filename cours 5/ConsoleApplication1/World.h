#pragma once
#include <vector>
#include "Entity.h"
#include "SFML/Graphics/RenderWindow.hpp"

class World {
public:
	std::vector<Entity*> data;
	void update(double dt);
	void draw(sf::RenderWindow& window);
};