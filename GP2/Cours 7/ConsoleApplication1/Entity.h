#pragma once
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

enum EType {
	Player,
	Brick,
	Wall,
	Ball,
	FX,
};


class Entity {
public:
	sf::Shape* spr = nullptr;
	sf::Vector2f lastGoodPos;
	EType			type;

	bool visible = true;
	bool simulated = true;

	int* gridSize;

	int cx = 0;
	int cy = 0;

	float rx = 0.0f;
	float ry = 0.0f;

	float dx = 0.0f;
	float dy = 0.0f;
		
	Entity(sf::Shape* _spr, int _cx, int _cy, int* gridSize) {
		spr = _spr;
		this->gridSize = gridSize;
		setPosition(_cx * *gridSize, _cy * *gridSize);
	}

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

		cx = x / *gridSize;
		cy = y / *gridSize;

		rx = x;
		while (rx > *gridSize) {
			rx -= *gridSize;
		}
		ry = y;
		while (ry > *gridSize) {
			ry -= *gridSize;
		}

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
	bool isColliding(int _cx, int _cy);
	bool CollisionWithWorld(std::vector<sf::Vector2f> vecs);
};

class PlayerPad : public Entity {
public:

	Entity* currentBall = nullptr;

	PlayerPad(EType type, sf::Shape* _spr) : Entity(type, _spr) {
		
	}

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