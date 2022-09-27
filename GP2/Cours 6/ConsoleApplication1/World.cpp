#include "World.h"
#include "SFML/Graphics/Texture.hpp"

void World::update(double dt) {
}


void World::draw(sf::RenderWindow& window) {
	for (auto e : data) {
		e->draw(window);
	}
}

Audio::Audio() {
}
