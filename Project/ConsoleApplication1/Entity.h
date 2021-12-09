#pragma once
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

enum CmdType {
	Move,
	Rotate,
};

struct Cmd {
	CmdType				type = Move;
	float				value = 0.0f;
	sf::Color			col;
	Cmd* next = nullptr;

	Cmd(CmdType t, float _value = 0.0) {
		type = t;
		value = _value;
	};

	Cmd* append(Cmd* nu) {
		if (next == nullptr)
			next = nu;
		else
			next = next->append(nu);
		return this;
	};

	Cmd* popFirst() {
		if (&next)
			return next;
		else
			return nullptr;
	};
};


enum EType {
	Player,
	Bot,
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

	//ajoute les cmds a la fin de la liste courante
	void appendCmd(Cmd* cmd) {
		if (cmds)
			cmds = cmds->append(cmd);
		else
			cmds = cmd;
	}

	void Translate(sf::Vector2f pos, float speed) { 
		targetPos = pos;
		appendCmd(new Cmd(CmdType::Move, speed)); 
	}
	virtual void update(double dt);
	virtual void draw(sf::RenderWindow& win);
	

protected:
	sf::Vector2f targetPos;
	Cmd* cmds = nullptr;
	Cmd* applyCmdInterp(Cmd* cmd, double dt);
};
bool CheckCollisionUsingRect(Entity* rect1, Entity* rect2);

class Laser : public Entity {	
	float reloading = 0.0f;
public:
	float reloadTime = .05f;

	float speed = 1000.0f;

	std::vector<float>	px;
	std::vector<float>	py;

	std::vector<float>	dx;
	std::vector<float>	dy;

	std::vector<bool>	alive;

	Laser(sf::Shape* _spr, sf::Color color = sf::Color::White) : Entity(EType::Bullet, _spr) {
		//spr->setFillColor(color);
	};
	void create(float _px, float _py, float _dx, float _dy);
	void ChangeDirection(int idx, float x, float y);
	virtual void update(double dt);
	virtual void draw(sf::RenderWindow& win);
};


class PlayerPad : public Entity {
public:

	PlayerPad(sf::Shape* _spr) : Entity(EType::Player, _spr) {
		
	}

	virtual void update(double dt);
	virtual void draw(sf::RenderWindow& win);
};


class Enemy : public Entity {
public :
	PlayerPad* p = nullptr;
	Laser* l = nullptr;
	int* interpSpeed;

	Enemy(sf::Shape* _spr, sf::Shape* lSpr, int* interp) : Entity(EType::Bot, _spr) {
		l = new Laser(lSpr, _spr->getFillColor());
		interpSpeed = interp;
	}

	PlayerPad* LookForPlayer(PlayerPad* pp, sf::Image rt, sf::Color clearColor);

	virtual void update(double dt);
	virtual void draw(sf::RenderWindow& win);
};
