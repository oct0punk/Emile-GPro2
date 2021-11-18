#include "World.h"

void World::update(double dt) {
	for (auto e : data) {
		e->update(dt);

		if (e->type == EType::Ball) {
			for (auto wall : data) {
				if (wall->type == EType::Wall)
					e->CheckCollision(wall, e);
				if (wall->type == EType::Brick && wall->visible) {
					if (e->CheckCollision(wall, e))
						wall->visible = false;

				}
			}
		}
	}
}


void World::draw(sf::RenderWindow& window) {
	for (auto e : data) {
		e->draw(window);
	}
}
