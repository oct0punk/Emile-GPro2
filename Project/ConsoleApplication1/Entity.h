#pragma once
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Mouse.hpp"

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
	Bullet,
	Bot,
	Wall,
	Power,
	FX,
	UI,
};

class Entity {
protected:
	double timeSinceLevelStart = 0.0;
	int health = 1;
	bool invincible = false;
	float invincibleTime = 1.0f;

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

	sf::Vector2f getPosition()					{ return spr->getPosition(); }
	virtual void setPosition(float x, float y)	{ spr->setPosition(sf::Vector2f(x, y)); }
	void setRotation(float angle)				{ return spr->setRotation(angle); }
	int getRotation()							{ return spr->getRotation(); }

	virtual bool ChangeHealth(int amount);
	void SetHealth(int value) {
		health = value;
	}
virtual void Revive() {
	SetHealth(3);
	visible = true;
	setPosition(800, 700);
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
virtual void Movement(double dt);

virtual void update(double dt);
virtual void draw(sf::RenderWindow& win);



protected:
	sf::Vector2f targetPos;
	Cmd* cmds = nullptr;
	Cmd* applyCmdInterp(Cmd* cmd, double dt);
};


class Particle : public Entity {
public:
	float originalTime;
	float time;
	sf::Color color;


	Particle(EType type, sf::Shape* _spr) : Entity(type, _spr) {
		originalTime = .3f + 50.0f * (rand() % 10 / 200.0f);
		time = originalTime;
		color = _spr->getFillColor();
	}

	virtual void update(double dt);
};


class Laser : public Entity {
public:
	float reloading = 0.0f;

	float speed = 3000.0f;

	std::vector<float>	px;
	std::vector<float>	py;

	std::vector<float>	dx;
	std::vector<float>	dy;

	std::vector<bool>	alive;
	std::vector<int>	power;

	Laser(sf::Shape* _spr, sf::Color color = sf::Color::White) : Entity(EType::Bullet, _spr) {
		spr->setFillColor(color);
	};
	void create(float _px, float _py, float _dx, float _dy, float rTime = 0.0f, int p = 1);
	void ChangeDirection(int idx, float x, float y);
	virtual void update(double dt);
	virtual void draw(sf::RenderWindow& win);
};


class PlayerPad : public Entity {
	float powerTime = 0.0f;

public:
	Laser* laser = nullptr;
	int speed = 800.0f;
	int power = 1;
	bool shootflag = true;
	sf::Color fColor = sf::Color(10, 100, 150);
	sf::Color oColor = sf::Color(230, 210, 85);
	sf::Color fColorInv = sf::Color(100, 0, 0);
	sf::Color oColorInv;

	PlayerPad(sf::Shape* _spr, Laser* l) : Entity(EType::Player, _spr) {
		laser = l;
	}

	virtual void update(double dt);
	virtual void draw(sf::RenderWindow& win);
	virtual bool ChangeHealth(int amount);
	virtual void Revive() {
		Entity::Revive();
		laser->visible = true;
		for (auto l : laser->alive)
			l = false;
		shootflag = true;		
		laser->reloading = 0.0f;
	}
	void Power();

};


class Enemy : public Entity {
public:
	PlayerPad* p = nullptr;

	Enemy(sf::Shape* _spr) : Entity(EType::Bot, _spr) {
		type = EType::Bot;
		health = 10;
	}

	// Slow the entity until stop
	void SlowDown(int speed);

	virtual bool ChangeHealth(int amount);
	virtual void update(double dt);
};


enum ButtonState {
	Normal,
	Selected,
	Clicked,
};


void PlayMode();
void BackToMenu();

class Button : public Entity {
	static sf::Color baseColor;
	static sf::Color selectedColor;
	static sf::Color clickedColor;

public:
	sf::Text text;
	ButtonState state = ButtonState::Normal;
	void (*action)(void);		// The button's function

	Button(sf::Shape* _spr, sf::Text* txt, void (*func)(void));

	virtual void setPosition(float x, float y) {
		spr->setPosition(sf::Vector2f(x, y));
		text.setPosition(x, y);
	}

	virtual void update(double dt) {
		switch (state)
		{
		case Normal:
			spr->setFillColor(baseColor);
			break;
		case Selected:
			spr->setFillColor(selectedColor);
			break;
		case Clicked:
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))	// Use button function
				action();
			spr->setFillColor(clickedColor);
			break;
		default:
			spr->setFillColor(baseColor);
			break;
		}
	}
	virtual void draw(sf::RenderWindow& win);

};
