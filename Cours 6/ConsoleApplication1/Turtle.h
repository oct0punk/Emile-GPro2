#pragma once
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "List.hpp"


enum cmdType {
	advance,
	Turn,
};

struct Command
{
	cmdType type;
	float time = 1;
	float factor = 1;
};


class Turtle {
	sf::CircleShape carapace;
	sf::CircleShape head;
	sf::CircleShape leftEye;
	sf::CircleShape rightEye;
	float direction = 90;
public:
	bool visible;

	List<Command*> list;

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

	void appendList(Command* cmd) {
		list.push_first(cmd);
	}

	Command* applyList(Command* cmd) {
		list.remove(cmd);
		return nullptr;
	}
};