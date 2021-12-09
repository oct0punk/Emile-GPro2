#include "World.h"
#include"Tool.hpp"
#include "SFML/Graphics/Texture.hpp"

void World::update(double dt) {

	bool coll = false;
	PlayerPad* p = nullptr;
	for (auto e : data) {
		if (e->type == Player) {
			p = (PlayerPad*)e;
			KeepEntityOnScreen(p);
			break;
		}
	}
	for (auto e : data) {
		e->update(dt * timeScale);
		switch (e->type) {
		case EType::Wall:
		{
			// Contact with player
			float distanceToP = LengthBtw(p->getPosition().x, p->getPosition().y, e->getPosition().x, e->getPosition().y);
			float radius = e->spr->getGlobalBounds().width / 2;
			if (distanceToP < radius) {
				sf::Vector2f moveP(p->getPosition() - e->getPosition());
				moveP.x *= radius / distanceToP;
				moveP.y *= radius / distanceToP;
				p->setPosition(e->getPosition().x + moveP.x, e->getPosition().y + moveP.y);
			}
			// Contact with ball
			for (auto b : data) { // Rebound
				if (b->type == Bullet) {
					Laser* l = (Laser*)b;
					for (int i = 1; i <= l->px.size(); i++) {
						sf::Vector2f bPos = sf::Vector2f(l->px[i - 1], l->py[i - 1]);
						float distance = LengthBtw(e->getPosition().x, e->getPosition().y, bPos.x, bPos.y);
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
		}	}	}	}	
		}
		break;
		case EType::Bot:
			Enemy* enemy = (Enemy*)e;
			// Collision with lasers
			for (auto b : data) {
				if (b->type == EType::Bullet) {
					Laser* l = (Laser*)b;
					for (int i = 0; i < l->px.size(); i++) {
						if (e->spr->getGlobalBounds().contains(sf::Vector2f(l->px[i], l->py[i]))) {
							e->visible = false;
			}	}	}	}
			
			KeepEntityOnScreen(e);
			// Enemy look for player
			enemy->p = enemy->LookForPlayer(p, Capture(window), *clearColor);
			break;
		}
	}
}


void World::draw(sf::RenderWindow& window) {
	window.clear(*clearColor);
	for (auto e : data) {
		e->draw(window);
	}
}

void World::KeepEntityOnScreen(Entity* e) {
	// Keep the entity inside screen's bounds
	sf::Vector2f pPos = e->getPosition();
	pPos.x = clamp(pPos.x, 10.0f, window->getSize().x - 10);
	pPos.y = clamp(pPos.y, 10.0f, window->getSize().y - 10);
	e->setPosition(pPos.x, pPos.y);
}

Audio::Audio() {
}
