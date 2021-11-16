#include "World.h"

void World::update(double dt) {
	for (auto e : data) {
		e->update(dt);
	}
}

void World::draw(sf::RenderWindow& window) {
	for (auto e : data) {
		e->draw(window);
	}
}
