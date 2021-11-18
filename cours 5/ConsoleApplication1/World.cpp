#include "World.h"

void World::update(double dt) {
	if (audio == nullptr)
		audio = new Audio();

	for (auto e : data) {
		e->update(dt);

		if (e->type == EType::Ball) {
			for (auto wall : data) {
				if (wall->type == EType::Wall) {
					e->CheckCollision(wall, e);
					audio->pong.play();
				}
				if (wall->type == EType::Brick && wall->visible) {
					if (e->CheckCollision(wall, e)) {
						wall->visible = false;
						audio->pong.play();
					}

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

Audio::Audio() {
	if (!pongBuffer.loadFromFile("res/pong.wav"))
		throw "no clip";
	else
		pong.setBuffer(pongBuffer);
	pong.setLoop(false);
}
