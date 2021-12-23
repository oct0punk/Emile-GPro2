#include "Entity.h"
#include "Tool.hpp"
#include "Game.h"
#include "Audio.h"
#include "SFML/Window/Keyboard.hpp"

void Entity::update(double dt) {
	timeSinceLevelStart += dt;
	if (!visible) return;
	if (cmds) applyCmdInterp(cmds, dt);

	sf::Vector2f move = getPosition();
	move.x += dx * dt;
	move.y += dy * dt;
	setPosition(move.x, move.y);

	if (type == EType::Wall)
		Movement(dt * 5);
	}


void Entity::draw(sf::RenderWindow& win) {
	if (visible)
		win.draw(*spr);
}


void Entity::Movement(double dt) {
	dx = sin(timeSinceLevelStart * dt) * 600 * dt;
	dy = cos(timeSinceLevelStart * .2f * dt) * 600 * dt;
}


Cmd* Entity::applyCmdInterp(Cmd* cmd, double dt) {
	//dt = 1.0f / 60.0f * 0.1;
	bool destroy = false;
	switch (cmd->type) {
	case Move:
	{
		sf::Vector2f dir = sf::Vector2f(targetPos - getPosition());
		if (Magnitude(dir) < cmds->value * dt) {
			destroy = true;
			break;
		}
		Normalize(&dir);
		dir *= cmds->value * (float)dt;
		dir += getPosition();
		setPosition(dir.x, dir.y);
	}
	break;
	case Rotate:
		break;
	default:
		destroy = true;
		break;
	}


	if (!destroy) {
		return cmd;
	}
	else {
		cmd = cmd->popFirst();
		return cmd;
	}
}




void PlayerPad::update(double dt) {
	dt /= Game::GetInstance()->world->timeScale;
	if (invincible) {
		spr->setFillColor(fColorInv);
		spr->setOutlineColor(oColorInv);
		invincibleTime -= dt;
		if (invincibleTime <= 0) {
			invincible = false;
			spr->setOutlineColor(oColor);
			spr->setFillColor(fColor);
		}
	} else {
		spr->setFillColor(fColor);
		spr->setOutlineColor(oColor);
	}

	// Moves
	bool keyHit = false;
	sf::Vector2f pPos = getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		pPos.y -= speed * dt;
		keyHit = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		pPos.y += speed * dt;
		keyHit = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		pPos.x -= speed * dt;
		keyHit = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		pPos.x += speed * dt;
		keyHit = true;
	}
	if (keyHit)
		setPosition(pPos.x, pPos.y);

	// Power
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && power > 0) {
		Power();
		powerTime = 4.2f;
		power--;
	}
	if (powerTime > 0.0f) {
		powerTime -= dt;
		if (powerTime <= 0.0f) {
			Game::GetInstance()->world->timeScale = 1.0f;
			Audio::GetInstance()->SetPitch(1.0f);
		}

	}
}


void PlayerPad::draw(sf::RenderWindow& win) {
	if (visible)
		win.draw(*spr);

}

bool PlayerPad::ChangeHealth(int amount) {
	if (invincible) return false;
	if (amount < 0) {
		invincible = true;
		invincibleTime = 1.0f;
		spr->setOutlineColor(oColorInv);
		spr->setFillColor(fColorInv);
	}
	health += amount;
	if (health < 0) {
		visible = false;
		Game::GetInstance()->state = GameState::GameOver;
		return true;
	}
	return false;
}

void PlayerPad::Power() {
	Game::GetInstance()->world->timeScale = 0.01f;
	Audio::GetInstance()->SetPitch(0.2f);
	Audio::GetInstance()->slow.play();
	laser->reloading = 0.0f;
}


bool Entity::ChangeHealth(int amount) {
	health += amount;
	if (health < 0) {
		visible = false;
		return true;
	}
	return false;
}




void Laser::create(float _px, float _py, float _dx, float _dy, float rTime, int p) {
	if (reloading > 0.0f) return;
	reloading = rTime;
	Audio::GetInstance()->Play(&Audio::GetInstance()->stdShot);

	sf::Vector2f dir(_dx, _dy);
	Normalize(&dir);
	float dx = dir.x;
	float dy = dir.y;
	for (int i = 0; i < px.size(); ++i) {
		if (!alive[i]) {
			px[i] = _px;
			py[i] = _py;
			this->dx[i] = dx;
			this->dy[i] = dy;
			alive[i] = true;
			power[i] = p;
			return;
		}
	}
	px.push_back(_px);
	py.push_back(_py);
	this->dx.push_back(dx);
	this->dy.push_back(dy);
	alive.push_back(true);
	power.push_back(p);
}


void Laser::ChangeDirection(int idx, float x, float y) {
	sf::Vector2f dir(x, y);
	Normalize(&dir);
	float acc = Magnitude(sf::Vector2f(dx[idx], dy[idx])) * 1.5f;
	dir.x *= acc;
	dir.y *= acc;
	dx[idx] = dir.x;
	dy[idx] = dir.y;
	power[idx] += 10;
	Audio::GetInstance()->Play(&Audio::GetInstance()->lHit);
}


void Laser::update(double dt) {
	if (reloading > 0.0f) {
		reloading -= dt;
	}
	for (int i = 0; i < px.size(); ++i) {
		if (alive[i]) {		// Move each shape into (dx ; dy)
			px[i] += dx[i] * speed * dt;
			py[i] += dy[i] * speed * dt;
			if (	// Check if outside screen
				(px[i] > 3000) || (px[i] < -100) ||
				(py[i] > 3000) || (py[i] < -100)
				) {
				alive[i] = false;
			}
		}
	}
}


void Laser::draw(sf::RenderWindow& win) {
	int idx = 0;
	const int sz = px.size();
	while (idx < sz) {
		if (alive[idx]) {
			auto b = spr;
			b->setRotation(atan2(dy[idx], dx[idx]) * 57.2958f);
			b->setPosition(sf::Vector2f(px[idx], py[idx]));
			win.draw(*b);
		}
		idx++;
	}
}




bool Enemy::ChangeHealth(int amount) {
	health += amount;
	if (health < 0) {
		visible = false;
		return true;
	}
	return false;
}


void Enemy::update(double dt)
{
	Entity::update(dt);

	if (p) {
		if (p->visible) {
			// Look at player
			sf::Vector2f intoP = p->getPosition() - getPosition();
			float targetAngle = atan2(intoP.y, intoP.x) * RadToDeg();
			setRotation(targetAngle);

			// Move into player
			int speed = 300;
			Normalize(&intoP);
			dx = intoP.x * speed;
			dy = intoP.y * speed;
		}
		else
		{
			if (abs(dx + dy) > 0)
				SlowDown(200 * dt);
		}
	}
}


void Enemy::SlowDown(int speed) {
	dx = clamp(0.0f, dx - speed, dx + speed);
	dy = clamp(0.0f, dy - speed, dy + speed);
}




void PlayMode()		{ Game::GetInstance()->state = GameState::Playing; }
void RetryButton()	{ Game::GetInstance()->Reset(); }


Button::Button(sf::Shape* _spr, sf::Text* txt, void(*func)(void)) : Entity(EType::UI, _spr) {
	text = *txt;
	action = func;
}

void Button::draw(sf::RenderWindow& win) {
	Entity::draw(win);
	win.draw(text);	
}


sf::Color Button::baseColor = sf::Color(sf::Color::Blue);
sf::Color Button::selectedColor = sf::Color(sf::Color::Cyan);
sf::Color Button::clickedColor = sf::Color(sf::Color(150, 50, 0));

void Particle::update(double dt) {
	Entity::update(dt);
	if (type == EType::Bot) {
		time -= dt;
		if (time > 0) {

			int r = lerp(time / originalTime, 0, color.r);
			int g = lerp(time / originalTime, 0, color.g);
			int b = lerp(time / originalTime, 0, color.b);
			int a = lerp(time / originalTime, 0, color.a);

			spr->setFillColor(sf::Color(r, g, b, a));
		}
		else
			visible = false;
	}
}
