#pragma once
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

enum CmdType {
	Translate,
	Rotate,
};

struct Cmd {
	CmdType				type = Translate;
	float				maxDuration = 0.333f;
	float				timer = 0.0f;
	float				value = 0.0f;
	float				originalValue = 0.0f;
	sf::Color			col;
	Cmd* next = nullptr;

	Cmd(CmdType t, float _value = 0.0) {
		type = t;
		value = _value;
		originalValue = value;
	};

	Cmd* append(Cmd* nu) {
		if (next == nullptr)
			next = nu;
		else
			next = next->append(nu);
		return this;
	};

	Cmd* popFirst() {
		Cmd* nu = next;
		delete this;
		return nu;
	};
};


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
	

protected:
	Cmd* cmds = nullptr;
	Cmd* applyCmdInterp(Cmd* cmd, double dt);
};
bool CheckCollisionUsingRect(Entity* rect1, Entity* rect2);



class PlayerPad : public Entity {
public:

	PlayerPad(EType type, sf::Shape* _spr) : Entity(type, _spr) {
		
	}

	virtual void update(double dt);
	virtual void draw(sf::RenderWindow& win);
};

class Laser : public Entity {	
	float reloading = 0.0f;
public:
	float reloadTime = .3f;

	float speed = 500.0f;

	std::vector<float>	px;
	std::vector<float>	py;

	std::vector<float>	dx;
	std::vector<float>	dy;

	std::vector<bool>	alive;

	Laser(EType type, sf::Shape* _spr) : Entity(type, _spr) {
	}
	void create(float _px, float _py, float _dx, float _dy);
	void ChangeDirection(int idx, float x, float y);
	virtual void update(double dt);
	virtual void draw(sf::RenderWindow& win);
};
