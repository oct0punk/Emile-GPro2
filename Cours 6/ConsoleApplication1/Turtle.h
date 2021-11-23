#pragma once
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "List.hpp"


class Turtle {
	sf::CircleShape carapace;
	sf::CircleShape head;
	sf::CircleShape leftEye;
	sf::CircleShape rightEye;
public:
	float direction = 90;
	bool visible;

	Turtle() {
		sf::Texture shellTexture;
		shellTexture.loadFromFile("res/shellTexture.jpg");
		shellTexture.setSmooth(true);

		sf::CircleShape carapace(60);
		carapace.setTexture(&shellTexture);
		sf::CircleShape head(20);
		head.setFillColor(sf::Color(100, 0, 0));
		sf::CircleShape leftEye(2);
		sf::CircleShape rightEye(2);

		leftEye.setOrigin(-80, 4);
		rightEye.setOrigin(-80, -4);
		carapace.setOrigin(60, 60);
		head.setOrigin(-50, 20);

		Turtle(carapace, head, leftEye, rightEye);
	}

	Turtle(sf::CircleShape carapace, sf::CircleShape head, sf::CircleShape leftE, sf::CircleShape rightE) {
		this->carapace = carapace;
		this->head = head;
		this->leftEye = leftE;
		this->rightEye = rightE;
	}

	void setPosition(float x, float y) {
		carapace.setPosition(sf::Vector2f(x, y));
		head.setPosition(sf::Vector2f(x, y));
		leftEye.setPosition(sf::Vector2f(x, y));
		rightEye.setPosition(sf::Vector2f(x, y));
	}

	void forward(float speed) {
		float degToRad = 0.0174533f;
		sf::Vector2f forward;
		forward.x = cos(direction * degToRad);
		forward.y = sin(direction * degToRad);
		setPosition((getPosition() + forward * speed).x, (getPosition() + forward * speed).y);
	}

	sf::Vector2f getPosition() {
		return carapace.getPosition();
	}

	void Rotate(float angle) {
		head.setRotation(angle);
		leftEye.setRotation(angle);
		rightEye.setRotation(angle);
		carapace.setRotation(angle + 90);
		direction = angle;
	}

	void RandomColor() {
		head.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
		carapace.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
		leftEye.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
		rightEye.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));;
	}

	void draw(sf::RenderWindow& win) {
		if (!visible) return;
		win.draw(head);
		win.draw(carapace);
		win.draw(leftEye);
		win.draw(rightEye);
	}
};


enum CmdType {
	Advance,
	Forward,
};

struct Cmd {
	CmdType type;
	float t;

public:
	Cmd(CmdType type, float time) {
		this->type = type;
		t = time;
	}

	Cmd() {
		t = 0;
	}
};

class CmdList {
	List<Cmd>* list;
	Turtle* turtle;
	
public:
	CmdList(Turtle* tortue) {
		list = new List<Cmd>(*new Cmd());
		turtle = tortue;
	};

	void update(double dt) {
		if (!list) return;
		if (list->val.t > 0) {
			if (list->val.type == CmdType::Advance) {
				turtle->forward(100 * dt);
				list->val.t -= dt;
			}
			else {
				turtle->Rotate(turtle->direction + 60 * dt);
				list->val.t -= dt;
			}
		}
		if (list->val.t <= 0)
			apply();
	}

	void append(CmdType type, float time) {
		list->push_back(*new Cmd(type, time));
	}

	void apply() {
		list = list->next;

	}
};