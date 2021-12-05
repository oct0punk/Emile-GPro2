#pragma once
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

enum EType {
	Player,
	Brick,
	Wall,
	Bullet,
	FX,
};


class Entity {
public:
	sf::Shape* spr = nullptr;
	sf::Vector2f lastGoodPos;
	EType			type;

	bool visible = true;
	float dx = 0.0f;
	float dy = 0.0f;
		

	Entity(EType type, sf::Shape* _spr) {
		this->type = type;
		lastGoodPos = sf::Vector2f(0, 0);
		spr = _spr;
	}

	~Entity() {
		if (spr) {
			delete spr;
			spr = nullptr;
		}
	}

	sf::Vector2f getPosition() {
		return spr->getPosition();
	}

	void setPosition(float x, float y) {
		spr->setPosition(sf::Vector2f(x, y));
	}

	void setRotation(float angle) {
		return spr->setRotation(angle);
	}

	int getRotation() {
		return spr->getRotation();
	}

	virtual void update(double dt);
	virtual void draw(sf::RenderWindow& win);
	bool CheckCollision(Entity* wall, Entity* ball);
};

class PlayerPad : public Entity {
public:

	PlayerPad(EType type, sf::Shape* _spr) : Entity(type, _spr) {
		
	}

	virtual void update(double dt);
	virtual void draw(sf::RenderWindow& win);
};

class LaserShot : public Entity {	
	float reloading = 0.0f;
public:
	float reloadTime = .3f;

	std::vector<float>	px;
	std::vector<float>	py;

	std::vector<float>	dx;
	std::vector<float>	dy;

	std::vector<bool>	alive;

	LaserShot(EType type, sf::Shape* _spr) : Entity(type, _spr) {
	}
	void create(float _px, float _py, float _dx, float _dy);
	virtual void update(double dt);
	virtual void draw(sf::RenderWindow& win);
};

class Particle : public Entity {

	float timeLeft;

public:
	Particle(EType type, sf::CircleShape* _spr, float time) : Entity(type, _spr){
		this->type = type;
		spr = _spr;
		timeLeft = time;
	}

	virtual void update(double dt);
	virtual void draw(sf::RenderWindow& win);
};