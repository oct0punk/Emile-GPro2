#include "World.h"
#include"Tool.hpp"
#include "SFML/Graphics/Texture.hpp"

void World::update(double dt) {

	bool coll = false;
	PlayerPad* p = nullptr;
	for (auto e : data) {
		if (e->type == Player) {
			p = (PlayerPad*)e;
			break;
		}
	}
	for (auto c : data) {
		c->update(dt * timeScale);
		if (c->type == Wall) {
			// Contact with player
			float distanceToP = LengthBtw(p->getPosition().x, p->getPosition().y, c->getPosition().x, c->getPosition().y);
			float radius = c->spr->getGlobalBounds().width / 2;
			if (distanceToP < radius) {
				sf::Vector2f moveP(p->getPosition() - c->getPosition());
				moveP.x *= radius / distanceToP;
				moveP.y *= radius / distanceToP;
				p->setPosition(c->getPosition().x + moveP.x, c->getPosition().y + moveP.y);
			}

			// Contact with ball
			for (auto b : data) { // Rebound
				if (b->type == Bullet) {
					Laser* l = (Laser*)b;
					for (int i = 1; i <= l->px.size(); i++) {
						sf::Vector2f bPos = sf::Vector2f(l->px[i - 1], l->py[i - 1]);
						float distance = LengthBtw(c->getPosition().x, c->getPosition().y, bPos.x, bPos.y);
						if (distance < c->spr->getGlobalBounds().width / 3)		// if rebound failed
						{
							l->alive[i - 1] = false;
							continue;
						}

						if (distance < c->spr->getGlobalBounds().width / 2) {
							sf::Vector2f rebound = Reflect(sf::Vector2f(l->dx[i - 1], l->dy[i - 1]), bPos - c->getPosition());
							l->px[i - 1] -= l->dx[i - 1] * dt * l->speed * 1.2f;			// Move the bullet to previous good position
							l->py[i - 1] -= l->dy[i - 1] * dt * l->speed * 1.2f;
							l->ChangeDirection(i - 1, rebound.x, rebound.y);	// Apply new direction to bullet							
						}

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
}
