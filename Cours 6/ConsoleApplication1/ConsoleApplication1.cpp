
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Tool.hpp"
#include <algorithm>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include "Entity.h"
#include "World.h"
#include "Turtle.h"

void ReadFile(CmdList& list) {
	FILE* file = nullptr;
	int count = list.Count();
	cout << count;
	fopen_s(&file, "res/command.txt", "rb");
	if (file && !feof(file)) {
		char line[256]{};

		for (;;) {
			int64_t nb = 0;
			fscanf_s(file, "%s %lli\n", line, 256, &nb);
			std::string s = line;
			if (s == "Rotate") {
				list.appendRotation(nb, 1);
			}
			if (s == "Forward") {
				list.appendTranslation(nb, 1);
			}
			if (s == "PenUp") {
				list.appendPen(false);
			}
			if (s == "PenDown") {
				list.appendPen(true);
			}
			if (feof(file))
				break;
		}
	}
	fclose(file);
	count = list.Count();
	cout << count;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1240, 720), "Turtle");
	window.setFramerateLimit(60);

	World world;

#pragma region SFML
	sf::Font fArial;
	if (!fArial.loadFromFile("res/arial.ttf"))
		cout << "font not loaded" << endl;
	sf::Text tDt;
	tDt.setFont(fArial);
	tDt.setFillColor(sf::Color::White);
	tDt.setCharacterSize(45);


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
	Turtle turtle(carapace, head, leftEye, rightEye);
	turtle.setPosition(400, 400);
#pragma endregion


	CmdList list(&turtle);
	struct _stat buf;
	_stat("res/command.txt", &buf);
	auto date = buf.st_mtime;



	double tStart		= getTimeStamp();
	double tEnterFrame	= getTimeStamp();
	double tExitFrame	= getTimeStamp();
	float radToDeg = 57.2958f;
	bool enterWasPressed = false;

	ReadFile(list);

	while (window.isOpen()) {
		sf::Event event;
		double dt = tExitFrame - tEnterFrame;
		tEnterFrame = getTimeStamp();
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}

		_stat("res/command.txt", &buf);
		if (date != buf.st_mtime) {
			turtle.Reset(window);	
			ReadFile(list);
			date = buf.st_mtime;
		}


		list.update(dt);

		float angle = turtle.direction;
		sf::Vector2f move = turtle.getPosition();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			turtle.forward(60 * dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) /*|| sf::Keyboard::isKeyPressed(sf::Keyboard::S)*/) {
			turtle.forward(-60 * dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			angle -= 60 * dt;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			angle += 60 * dt;
		}
		turtle.Rotate(angle);

		tDt.setString(to_string(dt) + " FPS:" + to_string((int)(1.0f / dt)));
		world.update(dt);

		window.clear(sf::Color(20, 20, 20));
		window.draw(tDt);
		turtle.draw(window);
		window.display();

		tExitFrame = getTimeStamp();
	}

	return 0;
}