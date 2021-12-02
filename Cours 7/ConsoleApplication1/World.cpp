#include "World.h"
#include "SFML/Graphics/Texture.hpp"

void World::update(double dt) {
	for (auto e : data) {
		e->update(dt);
	}
}


void World::draw(sf::RenderWindow& window) {
	for (auto e : data) {
		e->draw(window);
	}
	Entity* e = data[0];
	if (e) {

	}
}

Audio::Audio() {
}
