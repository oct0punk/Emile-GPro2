#include "World.h"
#include "SFML/Graphics/Texture.hpp"

void World::update(double dt) {
	if (audio == nullptr)
		audio = new Audio();

	for (auto e : data) {
		e->update(dt);

		if (e->type == EType::Ball) {
			e->setRotation(atan2(e->dy, e->dx) * 57.2958f + 180);
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
						for (int i = 0; i < 50; i++) {
							sf::CircleShape* fx = new sf::CircleShape(1);
							Particle* p = new Particle(EType::FX, fx, 1.0f);
							p->setPosition(wall->getPosition().x, wall->getPosition().y);
							p->dx = -100 + rand() % 100;
							p->dy = -100 + rand() % 100;
							particles.push_back(p);
						}
					}

				}
			}
		}
	}
	for (int i = 0; i < particles.size(); i++) {
		particles[i]->update(dt);
	}
}


void World::draw(sf::RenderWindow& window) {
	for (auto e : data) {
		e->draw(window);
	}
	for (auto e : particles) {
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
