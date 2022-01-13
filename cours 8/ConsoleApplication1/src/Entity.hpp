#pragma once

#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Entity;

class State {
public:
	sf::Color stateColor = sf::Color::Black;


	virtual void OnEnter(Entity* e);

	virtual void Update(Entity* e, double dt){}

};

class IdleState : public State {
	float life = .2f;

public:
	IdleState() {
		stateColor = sf::Color::White;
	}

	virtual void OnEnter(Entity* e);

	virtual void Update(Entity* e, double dt);
};

class WalkState : public State {
public:
	WalkState() {
		stateColor = sf::Color::Blue;
	}

	virtual void Update(Entity* e, double dt);
};

class RunState : public State {
public:
	RunState() {
		stateColor = sf::Color::Red;
	}

	virtual void Update(Entity* e, double dt);
};

class CoverState : public State {
public:
	CoverState() {
		stateColor = sf::Color(100, 0, 0);
	}

	virtual void Update(Entity* e, double dt);
};


class Entity {
public:
	sf::Shape*		spr = nullptr;

	bool			visible = true;

	float			cx = 0.0f; // Scaled position
	float			cy = 0.0f;
	float			rx = 0.0f; // Scaled position's rest
	float			ry = 0.0f;
	float			px = 0.0f; // Position in window
	float			py = 0.0f;

	float			dx = 0.0f;
	float			dy = 0.0f;

	float			gy = 0;

	float			frict_x = 0.1f;
	float			frict_y = .0f;

	inline static const int	stride = 32;

	State* currentState = nullptr;

	Entity(sf::Shape* _spr, float _cx, float _cy) {
		this->spr = _spr;
		cx = _cx;
		cy = _cy;
		syncSprite();

		currentState = new IdleState();
	}

	void			im();
	static bool			isColliding(int _cx, int _cy);
	virtual void	update(double dt);
	virtual void	draw(sf::RenderWindow& win);
	void			syncSprite();
	void ChangeState(State* newState);
};