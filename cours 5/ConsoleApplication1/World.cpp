#include "World.h"

void World::update(double dt) {
	for (auto e : data) {
		e->update(dt);

		if (e->type == EType::Ball) {
			for (auto wall : data) {
				if (wall->type == EType::Wall)
					e->CheckCollision(wall, e);
			}
		}
	}
}


void World::draw(sf::RenderWindow& window) {
	for (auto e : data) {
		e->draw(window);
	}
}
