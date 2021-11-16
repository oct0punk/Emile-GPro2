#include "World.h"

void World::update(double dt) {
	for (auto e : data) {
		e->update(dt);
	}
}

void World::draw(sf::RenderWindow& window) {
	for (auto e : data) {
		e->draw(window);
		if (e->type == EType::Ball) {
			if (e->getPosition().x - 10 < 0 || e->getPosition().x + 10 > window.getSize().x)
				e->dx *= -1;
			if (e->getPosition().y - 10 < 0 || e->getPosition().y + 10 > window.getSize().y)
				e->dy *= -1;
		}
	}
}
