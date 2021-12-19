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
	Bot,
	Wall,
	Bullet,
	UI,
};


class Entity {
	double timeSinceLevelStart = 0.0;
	int health = 1;

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
	virtual void setPosition(float x, float y) {
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

	virtual void Movement(double dt);
	

protected:
	sf::Vector2f targetPos;
	Cmd* cmds = nullptr;
	Cmd* applyCmdInterp(Cmd* cmd, double dt);
};
bool CheckCollisionUsingRect(Entity* rect1, Entity* rect2);

class Laser : public Entity {	
	float reloading = 0.0f;
public:
	float reloadTime = .1f;

	float speed = 3000.0f;

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
	bool invincible = false;
	float invincibleTime = 1.0f;

	PlayerPad(sf::Shape* _spr) : Entity(EType::Player, _spr) {
		
	}

	virtual void update(double dt);
	virtual void draw(sf::RenderWindow& win);
	virtual bool ChangeHealth(int amount) {
		if (invincible) return false;
		health += amount;
		invincible = true;
		invincibleTime = 1.0f;
		spr->setFillColor(sf::Color::Red);
		if (health < 0) {
			visible = false;
			return true;
		}
		return false;
	}

	int health = 3;
protected :
};


class Enemy : public PlayerPad {
public :
	PlayerPad* p = nullptr;
	bool invincible = false;
	float invincibleTime = 1.0f;

	Enemy(sf::Shape* _spr) : PlayerPad(_spr) {
		type = EType::Bot;
		health = 10;
	}

	PlayerPad* LookForPlayer(PlayerPad* pp, sf::Image rt, sf::Color clearColor);
	void SlowDown(int speed);

	virtual bool ChangeHealth(int amount);
	virtual void update(double dt);
	virtual void draw(sf::RenderWindow& win);
};


enum ButtonState {
	Normal,
	Selected,
	Clicked,
};


// Button methods
void PlayMode();

class Button : public Entity {
	static sf::Color baseColor;
	static sf::Color selectedColor;
	static sf::Color clickedColor;

public:
	sf::Text text;
	ButtonState state = ButtonState::Normal;
	void (*action)(void);		// The button's function

	Button(sf::Shape* _spr, sf::Text* txt);

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
