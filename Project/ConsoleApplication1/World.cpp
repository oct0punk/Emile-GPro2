#include "World.h"
#include"Tool.hpp"
#include "SFML/Graphics/Texture.hpp"

void World::updateGame(double dt) {

	bool coll = false;
	PlayerPad* p = nullptr;
	for (auto e : dataPlay) {
		if (e->type == Player) {
			p = (PlayerPad*)e;
			KeepEntityOnScreen(p);
			break;
		}
	}
	for (auto e : dataPlay) {
		e->update(dt);
		switch (e->type) {
		case EType::Wall:
		{
			float distanceToP = Magnitude(p->getPosition().x, p->getPosition().y, e->getPosition().x, e->getPosition().y);
			float radius = e->spr->getGlobalBounds().width / 2;
			// The obstacle rebound on the screen edges
			sf::Vector2f pos = e->getPosition();
			if (e->getPosition().x < -radius * 3)
				pos.x = window->getSize().x + radius * 2;
			if (e->getPosition().x > window->getSize().x + radius * 3)
				pos.x = -radius * 2;
			if (e->getPosition().y < -radius * 3)
				pos.y = window->getSize().y + radius * 2;
			if (e->getPosition().y > window->getSize().y + radius * 3)
				pos.y = -radius * 2;
			e->setPosition(pos.x, pos.y);

			// Contact with player
			if (distanceToP < radius) {
				sf::Vector2f moveP(p->getPosition() - e->getPosition());
				moveP.x *= radius / distanceToP;
				moveP.y *= radius / distanceToP;
				p->setPosition(e->getPosition().x + moveP.x, e->getPosition().y + moveP.y);
			}
			// Contact with ball
			for (auto b : dataPlay) { // Rebound
				if (b->type == Bullet) {
					Laser* l = (Laser*)b;
					for (int i = 1; i <= l->px.size(); i++) {
						sf::Vector2f bPos = sf::Vector2f(l->px[i - 1], l->py[i - 1]);
						float distance = Magnitude(e->getPosition().x, e->getPosition().y, bPos.x, bPos.y);
						if (distance < e->spr->getGlobalBounds().width / 3)		// if rebound failed
						{
							l->alive[i - 1] = false;
							continue;
						}

						if (distance < e->spr->getGlobalBounds().width / 2) {
							sf::Vector2f rebound = Reflect(sf::Vector2f(l->dx[i - 1], l->dy[i - 1]), bPos - e->getPosition());
							l->px[i - 1] -= l->dx[i - 1] * dt * l->speed * 1.2f;			// Move the bullet to previous good position
							l->py[i - 1] -= l->dy[i - 1] * dt * l->speed * 1.2f;
							l->ChangeDirection(i - 1, rebound.x, rebound.y);	// Apply new direction to bullet							
						}
					}
				}
			}
			break;
		}
		case EType::Bot:
		{
			Enemy* enemy = (Enemy*)e;
			// Collision with lasers
			for (auto b : dataPlay) {
				if (b->type == EType::Bullet) {
					Laser* l = (Laser*)b;
					for (int i = 0; i < l->px.size(); i++) {
						if (!l->alive[i]) break;
						if (e->spr->getGlobalBounds().contains(sf::Vector2f(l->px[i], l->py[i]))) {
							if (e->visible) {
								if (enemy->ChangeHealth(-1))
									eCount--;
								l->alive[i] = false;
							}
						}
					}
				}
			}
			
			if (p->visible)
				KeepEntityOnScreen(e);

			// Contact with player
			if (Magnitude(e->getPosition() - p->getPosition()) < 150)
				if (e->visible && p->visible)
					p->ChangeHealth(-1);
			break;
		}
		}
	}
}

void World::drawGame(sf::RenderWindow& window) {
	window.clear(*clearColor);
	for (auto e : dataPlay) {
		e->draw(window);
	}
}


void World::KeepEntityOnScreen(Entity* e, float value) {
	// Keep the entity inside screen's bounds
	sf::Vector2f pPos = e->getPosition();
	pPos.x = clamp(pPos.x, value, window->getSize().x - value);
	pPos.y = clamp(pPos.y, value, window->getSize().y - value);
	e->setPosition(pPos.x, pPos.y);
}


void World::PushEntity(Entity* e, sf::Vector2f pos) {
	bool inserted = false;
	int idx = 0;
	for (auto entity : dataPlay) {
		if (entity->type == e->type) {
			if (!entity->visible) {
				inserted = true;
				entity->visible = true;
				entity->setPosition(pos.x, pos.y);
				break;
			}
		}
		idx++;
	}
	if (!inserted) dataPlay.push_back(e);



	if (e->type == EType::Bot) {
		eCount++;
		Enemy* enemy = (Enemy*)dataPlay[idx];
		if (inserted) 
			enemy->ChangeHealth(10);
		for (auto b : dataPlay) {
			if (b->type == Player) {
				enemy->p = (PlayerPad*)b;
				break;
			}
		}
	}
	e->setPosition(pos.x, pos.y);
}

void World::SpawnEnemy(sf::Vector2f pos) {
	using namespace sf;
	ConvexShape* eShape = new ConvexShape(4);
	eShape->setPoint(0, Vector2f(0, 0));
	eShape->setPoint(1, Vector2f(80, 20));
	eShape->setPoint(2, Vector2f(0, 40));
	eShape->setPoint(3, Vector2f(20, 20));
	eShape->setOrigin(Vector2f(20, 20));
	eShape->setFillColor(Color::Transparent);
	eShape->setOutlineThickness(3);

	PushEntity(new Enemy(eShape), pos);

}

void World::SpawnObstacle(int radius) {
	sf::CircleShape* wShape = new sf::CircleShape(radius);
	wShape->setOrigin(wShape->getRadius(), wShape->getRadius());
	wShape->setFillColor(sf::Color::Transparent);
	wShape->setOutlineThickness(radius / 7);
	wShape->setOutlineColor(sf::Color::Cyan);
	Entity* w = new Entity(EType::Wall, wShape);
	w->setPosition(-radius, -radius);
	dataPlay.push_back(w);
}

