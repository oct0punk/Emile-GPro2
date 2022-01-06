
#include "Entity.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "imgui.h"
#include "Game.hpp"

using namespace sf;

void Entity::syncSprite() {
	px = (cx + rx) * stride;
	py = (cy + ry) * stride;
	spr->setPosition(px, py);
}

void Entity::ChangeState(State* newState) {

	delete currentState;
	currentState = newState;
	currentState->OnEnter(this);
}

void Entity::im() {
	using namespace ImGui;

	bool modified = false;
	modified |= DragFloat("dx", &dx, 1);
	modified |= DragFloat("dy", &dy, 1);

	modified |= DragFloat("gy", &gy, 0.001f);

	modified |= DragFloat("frict_x", &frict_x, 0.01f);
	modified |= DragFloat("frict_y", &frict_y, 0.01f);

	modified |= DragFloat("cx", &cx, 1.0f);
	modified |= DragFloat("cy", &cy, 1.0f);
	modified |= DragFloat("rx", &rx, 0.05f);
	modified |= DragFloat("ry", &ry, 0.05f);
	Value("px", (float)px);
	Value("py", (float)py);
	if (modified)
		syncSprite();
}

bool Entity::isColliding(int ccx, int ccy) {
	if (ccx < 0)
		return true;
	if (ccy < 0)
		return true;

	if (ccx >= 1280 / stride)
		return true;

	if (ccy >= 720 / stride)
		return true;

	for (auto& vi : Game::walls)
		if ((vi.x == ccx) && (vi.y == ccy))
			return true;

	return false;
}

void Entity::update(double dt) {
	currentState->Update(this, dt);

	dy += gy * dt;
	rx += dt * dx;
	ry += dt * dy;

	dx *= pow(frict_x, dt * 60.0f);
	dy *= pow(frict_y, dt * 60.0f);

	while (rx >= 1) {
		if (isColliding(cx + 1, cy)) {
			dx = 0;
			rx = 0.9;
		}
		else {
			rx--;
			cx++;
		}
	}
	while (rx <= 0) {
		if (isColliding(cx - 1, cy)) {
			dx = 0;
			rx = 0.1; // - 2.3 -> - 0.3
		}
		else {
			rx++;
			cx--;
		}
	}

	while (ry >= 1) {
		if (isColliding(cx, cy + 1)) {
			dy = 0;
			ry = 0.999f;
		}
		else {
			ry--;
			cy++;
		}
	}

	while (ry <= 0) {
		if (isColliding(cx, cy - 1)) {
			dy = 0.0f;
			ry = 0.1f;
		}
		else {
			ry++;
			cy--;
		}
	}
	syncSprite();

}

void Entity::draw(sf::RenderWindow& win) {
	if (visible)
		win.draw(*spr);
}




void State::OnEnter(Entity* e) {
	e->spr->setFillColor(stateColor);
}

void IdleState::OnEnter(Entity* e) {
	State::OnEnter(e);
	life = .2f;
}

void IdleState::Update(Entity* e, double dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		e->ChangeState(new WalkState());
		return;
	}

	life -= dt;
	if (life < 0) {
		if (e->isColliding(e->cx + 1, e->cy)) e->ChangeState(new CoverState());
		if (e->isColliding(e->cx - 1, e->cy)) e->ChangeState(new CoverState());
		if (e->isColliding(e->cx, e->cy + 1)) e->ChangeState(new CoverState());
		if (e->isColliding(e->cx, e->cy - 1)) e->ChangeState(new CoverState());
	}

}

void WalkState::Update(Entity* e, double dt) {
	float max_speed_x = 5;
	float max_speed_y = 30;

	static bool wasPressedUp = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		e->dx -= max_speed_x * 100;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		e->dx += max_speed_x * 100;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		e->dy -= max_speed_y * 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		e->dy += max_speed_y * 2;
	}

	e->dx = clamp(e->dx, -max_speed_x, max_speed_x);
	e->dy = clamp(e->dy, -max_speed_y, max_speed_y);

	if (abs(e->dx) < .1f)
		e->ChangeState(new IdleState());
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		e->ChangeState(new RunState());
}

void RunState::Update(Entity* e, double dt) {
	float max_speed_x = 20;
	float max_speed_y = 30;

	static bool wasPressedUp = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		e->dx -= max_speed_x * 100;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		e->dx += max_speed_x * 100;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		e->dy -= max_speed_y * 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		e->dy += max_speed_y * 2;
	}

	e->dx = clamp(e->dx, -max_speed_x, max_speed_x);
	e->dy = clamp(e->dy, -max_speed_y, max_speed_y);

	if (abs(e->dx) < .1f)
		e->ChangeState(new IdleState());
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		e->ChangeState(new WalkState());
}

void CoverState::Update(Entity* e, double dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		e->ChangeState(new WalkState());

}
