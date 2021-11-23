#pragma once
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML//Graphics.hpp"
#include "List.hpp"


class Turtle {
	std::vector<sf::CircleShape> shapes;
	std::vector<sf::CircleShape> vertices;
public:
	sf::Color circleColor = sf::Color(100, 50, 0);
	float direction = 90;
	bool visible = true;
	bool penDown = true;

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
		shapes.push_back(head);
		shapes.push_back(leftE);
		shapes.push_back(rightE);
		shapes.push_back(carapace);
		
		penDown = true;
	}

	void setPosition(float x, float y) {
		for (int i = 0; i < shapes.size(); i++) {
			shapes[i].setPosition(sf::Vector2f(x, y));
		}
		if (penDown) {
			int r = rand() % 20 - 10;
			if (r < 0)
				r = 0;
			sf::CircleShape c(-r);
			c.setFillColor(circleColor);
			c.setOrigin(sf::Vector2f(r, r));
			c.setPosition(sf::Vector2f(x, y));
			vertices.push_back(c);
		}
	}

	void forward(float speed) {
		float degToRad = 0.0174533f;
		sf::Vector2f forward;
		forward.x = cos(direction * degToRad);
		forward.y = sin(direction * degToRad);
		setPosition((getPosition() + forward * speed).x, (getPosition() + forward * speed).y);
	}

	sf::Vector2f getPosition() {
		return shapes[0].getPosition();
	}

	void Rotate(float angle) {
		for (int i = 0; i < shapes.size(); i++)
			shapes[i].setRotation(angle);
		direction = angle;
	}

	void RandomColor() {
		circleColor = sf::Color(
			rand() % 255,
			rand() % 255,
			rand() % 255);
	}

	void draw(sf::RenderWindow& win) {
		if (!visible) return;
		for (auto c : vertices)
			win.draw(c);
		for (int i = 0; i < shapes.size(); i++)
			win.draw(shapes[i]);
	}
};


#pragma region Command
enum CmdType {
	Advance,
	Rotate,
	//PenUp, 
	//PenDown,
};

struct Cmd {
	CmdType type;
	float factor = 1.5f;
	float t;

public:
	Cmd(CmdType type, float factor, float time) {
		this->type = type;
		this->factor = factor;
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
		if (list->val.t >= 0) {
			switch (list->val.type)
			{
			case Advance:
				turtle->forward(list->val.factor * dt);
				list->val.t -= dt;
				break;
			case Rotate:
				turtle->Rotate(turtle->direction + list->val.factor * dt);
				list->val.t -= dt;
				break;
			//case PenUp
			//	turtle->penDown = false;
			//	list->val.t -= dt;
			//	break;
			//case PenDown:
			//	turtle->penDown = true;
			//	list->val.t -= dt;
			//	break;
			default:
				apply();
				break;
			}
		}
		else
			apply();
	}

	void appendTranslation(float speed, float time) {
		list->push_back(*new Cmd(CmdType::Advance, speed, time));
	}

	void appendRotation(float deltaAngle, float time) {
		list->push_back(*new Cmd(CmdType::Rotate, deltaAngle, time));
	}

	//void appendPen(bool down) {
	//	float f = 0.0f;
	//	CmdType t = CmdType::PenUp;
	//	if (down) {
	//		t = CmdType::PenDown;
	//		f = 1.0f;
	//	}
	//	list->push_back(*new Cmd(t, f, 0));
	//}

	void apply() {
		List<Cmd>* current = list;
		list = list->next;
		delete current;
	}
};
#pragma endregion