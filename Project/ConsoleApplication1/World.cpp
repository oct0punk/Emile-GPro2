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
	for (auto e : data) {
		e->update(dt * timeScale);
		if (e->type == Wall) {
			if (LengthBtw(e->getPosition().x, e->getPosition().y, p->getPosition().x, p->getPosition().y)
				< e->spr->getGlobalBounds().width / 2)
				p->visible = false;

			for (auto b : data) { // Rebound
				if (b->type == Bullet) {
					Laser* l = (Laser*)b;
					for (int i = 1; i <= l->px.size(); i++) {
						sf::Vector2f bPos = sf::Vector2f(l->px[i - 1], l->py[i - 1]);
						float distance = LengthBtw(e->getPosition().x, e->getPosition().y, bPos.x, bPos.y);
						if (distance < e->spr->getGlobalBounds().width / 3)
						{
							l->alive[i - 1] = false;
							continue;
						}

						if (distance < e->spr->getGlobalBounds().width / 2) {
							sf::Vector2f rebound = Reflect(sf::Vector2f(l->dx[i - 1], l->dy[i - 1]), bPos - e->getPosition());

							l->px[i - 1] -= l->dx[i - 1] * dt * 1.2f;			// Move back the bullet
							l->py[i - 1] -= l->dy[i - 1] * dt * 1.2f;
							l->dx[i - 1] = rebound.x * 500.0f;		// Apply new direction to bullet
							l->dy[i - 1] = rebound.y * 500.0f;
							return;
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
