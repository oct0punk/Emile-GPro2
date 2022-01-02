#include "World.h"
#include"Tool.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "Game.h"
#include "Command.h"
#include "Audio.h"
#include <SFML/Window/Keyboard.hpp>

void World::updateGame(double dt) {
	bool coll = false;
	PlayerPad* p = Game::GetInstance()->player;
	p->update(dt);
	KeepEntityOnScreen(p);
	dt *= timeScale;
	if (flashTime > 0.0f)
		flashTime -= dt * 14.0f;

	for (auto e : dataPlay) {
		if (!e->visible || e->type == Player) continue;
		e->update(dt);

		switch (e->type) {
		case EType::Wall:
		{
			float distanceToP = Magnitude(p->getPosition().x, p->getPosition().y, e->getPosition().x, e->getPosition().y);
			float radius = e->spr->getGlobalBounds().width / 2;
			// The obstacle rebound on edges outside the screen
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
			// Contact with laser
			for (auto b : dataPlay) { // Rebound
				if (b->type == Bullet) {
					Laser* l = (Laser*)b;
					for (int i = 1; i <= l->px.size(); i++) {
						sf::Vector2f bPos = sf::Vector2f(l->px[i - 1], l->py[i - 1]);
						float distance = Magnitude(e->getPosition().x, e->getPosition().y, bPos.x, bPos.y);

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
						if (!l->alive[i]) continue;
						if (e->spr->getGlobalBounds().contains(sf::Vector2f(l->px[i], l->py[i]))) {
							if (e->visible) {
								Game::GetInstance()->score += 1;
								if (enemy->ChangeHealth(-l->power[i])) {
									eCount--;
									Game::GetInstance()->score += 10 * (l->power[i] / 1.9f);
									scoretxt->setString(to_string(Game::GetInstance()->score));
									flashTime = pi();
									// FX
									for (int i = 0; i < 40; i++) {
										sf::CircleShape* cShape = new sf::CircleShape(2 + rand() % 10);
										cShape->setFillColor(sf::Color(255 - rand() % 25, rand() % 50, 0));
										Particle* p = new Particle(EType::Bot, cShape);
										p->dx =  cos(i * rand() % 300) * RadToDeg();
										p->dy =  sin(i * rand() % 300) * RadToDeg();
										p->setPosition(e->getPosition().x, e->getPosition().y);
										bool inserted = false;
										dataFX.push_back(p);
									}
								}
								l->alive[i] = false;
								Audio::GetInstance()->Play(&Audio::GetInstance()->hit);
							}
						}
					}
				}
			}
			
			//if (p->visible)
			//	KeepEntityOnScreen(e);

			// Contact with player
			if (Magnitude(e->getPosition() - p->getPosition()) < 150 && timeScale >= 1.0f)
				if (e->visible && p->visible) {
					p->ChangeHealth(-1);
					Game::GetInstance()->pHit = true;
				}
			break;
		}
		case EType::Power:
			// Collision with lasers
			for (auto b : dataPlay) {
				if (b->type == EType::Bullet) {
					Laser* l = (Laser*)b;
					for (int i = 0; i < l->px.size(); i++) {
						if (!l->alive[i]) break;
						if (e->spr->getGlobalBounds().contains(sf::Vector2f(l->px[i], l->py[i]))) {
							if (e->ChangeHealth(-l->power[i])) {
								p->power++;
								Audio::GetInstance()->Play(&Audio::GetInstance()->power);
							}
							l->alive[i] = false;
							Audio::GetInstance()->Play(&Audio::GetInstance()->hit);

						}
					}
				}
			}
		}

		for (auto p : dataFX)
			p->update(dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
		if (pauseKeyUp) {
			Game::GetInstance()->ChangeState(GameState::Pause);
			pauseKeyUp = false;
		}
	}
	else
		pauseKeyUp = true;
}


void World::updateMenu(double dt) {
	for (auto e : dataMenu) {
		e->update(dt);
		if (Controls::GetInstance()->isConnected) {
			selectedButton->state = ButtonState::Selected;
			if (sf::Joystick::isButtonPressed(0, 0))
				selectedButton->action();

		} else {
			sf::Vector2f mPos(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
			if (e->spr->getGlobalBounds().contains(mPos))
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					e->state = ButtonState::Clicked;
				else
					e->state = ButtonState::Selected;
			else
				e->state = ButtonState::Normal;
		}
	}
}


void World::updatePause(double dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
		if (pauseKeyUp) {
			Game::GetInstance()->ChangeState(GameState::Playing);
			pauseKeyUp = false;
		}
	}
	else
		pauseKeyUp = true;
}


void World::updateGameOver(double dt) {
	for (auto e : dataGameOver) {
		e->update(dt);
		if (Controls::GetInstance()->isConnected) {
			selectedButton->state = ButtonState::Selected;
			if (sf::Joystick::isButtonPressed(0, 0))
				selectedButton->action();

		}
		else {
			sf::Vector2f mPos(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
			if (e->spr->getGlobalBounds().contains(mPos))
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					e->state = ButtonState::Clicked;
				else
					e->state = ButtonState::Selected;
			else
				e->state = ButtonState::Normal;
		}
	}
}



void World::drawGame(sf::RenderWindow& window) {
	sf::Color clear = *clearColor;
	if (flashTime > 0.0f) {
		clear.r = lerp(sin(flashTime), clearColor->r, clearColor->r + 40);
		clear.g = lerp(sin(flashTime), clearColor->g, clearColor->g + 40);
		clear.b = lerp(sin(flashTime), clearColor->b, clearColor->b + 40);
	}
	window.clear(clear);
	for (auto p : dataFX)
		p->draw(window);
	for (auto e : dataPlay) {
		e->draw(window);
	}
	window.draw(*scoretxt);
}


void World::drawMenu(sf::RenderWindow& win) {
	win.clear(*clearColor);
	for (auto e : dataMenu) {
		e->draw(win);
	}
	win.draw(credit);
}


void World::drawGameOver(sf::RenderWindow& win) {
	win.clear(*clearColor);
	for (auto e : dataGameOver) {
		e->draw(win);
	}
	win.draw(*scoretxt);
}




void World::PushFX(Particle* p) {
	for (auto e : dataFX) {
		if ((!e->visible)) {
			e = new Particle(*p);
			return;
		}
	}
	dataFX.push_back(p);
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
	e->setPosition(pos.x, pos.y);


	if (e->type != EType::Bot) return;
	eCount++;
	Enemy* enemy = (Enemy*)dataPlay[idx];
	enemy->SetHealth(Game::GetInstance()->EnemyHealth());
	for (auto b : dataPlay) {
		if (b->type == Player) {
			enemy->p = (PlayerPad*)b;
			break;
		}
	}
	
}


void World::SpawnEnemy(sf::Vector2f pos) {
	using namespace sf;
	ConvexShape* eShape = new ConvexShape(4);
	eShape->setPoint(0, Vector2f(0, 0));
	eShape->setPoint(1, Vector2f(80, 20));
	eShape->setPoint(2, Vector2f(0, 40));
	eShape->setPoint(3, Vector2f(20, 20));
	eShape->setOrigin(Vector2f(20, 20));
	eShape->setOutlineThickness(7);
	eShape->setFillColor(	sf::Color::Blue);
	eShape->setOutlineColor(sf::Color::White);

	PushEntity(new Enemy(eShape), pos);

}


void World::SpawnObstacle(int radius, sf::Vector2f pos) {
	sf::CircleShape* wShape = new sf::CircleShape(radius);
	wShape->setOrigin(wShape->getRadius(), wShape->getRadius());
	wShape->setFillColor(sf::Color::Transparent);
	wShape->setOutlineThickness(radius / 7);
	wShape->setOutlineColor(rand() % 2 == 0 ? sf::Color::Red : sf::Color::Cyan);
	Entity* w = new Entity(EType::Wall, wShape);
	w->setPosition(pos.x, pos.y);
	dataPlay.push_back(w);
}


void World::InstantiatePower() {
	sf::CircleShape* cShape = new sf::CircleShape(20);
	cShape->setOrigin(20, 20);
	sf::Texture* watch = new sf::Texture();
	watch->loadFromFile("res/watch.png");
	cShape->setTexture(watch);
	cShape->setOutlineThickness(4);
	cShape->setOutlineColor(sf::Color::Yellow);
	Entity* power = new Entity(EType::Power, cShape);
	PushEntity(power);
	power->dx = -20;
	power->dy = 5;
	power->setPosition(1030, 250);
	power->SetHealth(20);
}



void World::KeepEntityOnScreen(Entity* e, float value) {
	// Keep the entity inside screen's bounds
	sf::Vector2f pPos = e->getPosition();
	pPos.x = clamp(pPos.x, value, window->getSize().x - value);
	pPos.y = clamp(pPos.y, value, window->getSize().y - value);
	e->setPosition(pPos.x, pPos.y);
}