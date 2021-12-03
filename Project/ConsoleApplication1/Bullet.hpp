#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Shape.hpp"

class Bullet { 
public:
	sf::Shape* b;

	std::vector<float>	px;
	std::vector<float>	py;

	std::vector<float>	dx;
	std::vector<float>	dy;

	std::vector<bool>	alive;

	Bullet(sf::Shape* spr) {
		b = spr;
	}

	void create(float px, float py, float dx, float dy);
	void update(double dt);

	void draw(sf::RenderWindow& win);
};