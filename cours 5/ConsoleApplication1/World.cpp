#include "World.h"

void World::update(double dt) {
	if (audio == nullptr)
		audio = new Audio();

	for (auto e : data) {
		e->update(dt);

		if (e->type == EType::Ball) {
			for (auto wall : data) {
				if (wall->type == EType::Wall || wall->type == EType::Player) {
					if (e->CheckCollision(wall, e))
						audio->pong.play();
				}
				if (wall->type == EType::Brick && wall->visible) {
					if (e->CheckCollision(wall, e)) {
						e->setPosition(e->lastGoodPos.x, e->lastGoodPos.y);
						wall->visible = false;
						audio->pong.play();
						// FX
						//Particle* p = new Particle(EType::FX, new sf::CircleShape(5), 0.2f);
						//p->setPosition(wall->getPosition().x, wall->getPosition().y);
						//p->dx = -100 + rand() % 100;
						//p->dy = -100 + rand() % 100;
						//data.push_back(p);
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
