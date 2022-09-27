
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

#include "imgui.h"
#include "imgui-SFML.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1240, 720), "Turtle");
	window.setFramerateLimit(60);

	World world;
	world.gridSize = new int(16);

	sf::Font fArial;
	if (!fArial.loadFromFile("res/arial.ttf"))
		cout << "font not loaded" << endl;
	sf::Text tDt;
	tDt.setFont(fArial);
	tDt.setFillColor(sf::Color::White);
	tDt.setCharacterSize(45);

	sf::RectangleShape* rect = new sf::RectangleShape(sf::Vector2f(50, 50));
	rect->setFillColor(sf::Color::Yellow);
	sf::RectangleShape* ground = new sf::RectangleShape(sf::Vector2f(5050, 50));
	ground->setFillColor(sf::Color::Cyan);

	Entity p(rect, 5, 6, world.gridSize);

	world.data.push_back(&p);

	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();
	float radToDeg = 57.2958f;


	ImGui::SFML::Init(window);
	sf::Clock deltaClock;
	float angle = 0;
	int distance = 100;
	sf::Color clearColor(20, 20, 20, 20);
	sf::Color penColor(20, 20, 20, 20);
	float speed = 1;

	while (window.isOpen()) {
		sf::Event event;
		double dt = tExitFrame - tEnterFrame;
		tDt.setString(to_string(dt) + " FPS:" + to_string((int)(1.0f / dt)));
		tEnterFrame = getTimeStamp();

		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}

		ImGui::SFML::Update(window, deltaClock.restart());
		ImGui::ShowDemoWindow();
		ImGui::Begin("Commands");

		ImGui::Value("cx", p.cx); ImGui::SameLine();
		ImGui::Value("cy", p.cy);
		ImGui::Value("rx", p.rx); ImGui::SameLine();
		ImGui::Value("ry", p.ry);
		ImGui::Value("acceleration", p.dy);
		ImGui::Separator();
		ImGui::InputFloat("Speed", &speed, 0.0f, 100.0f);
		ImGui::DragInt("GridSize", world.gridSize , 1.0f, 1.0f, 2000);
		ImGui::End();
		
		float x = p.getPosition().x;
		float y = p.getPosition().y;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			x -= speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			x += speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			y -= speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			y += speed;
		p.setPosition(x, y);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			world.AppendBlock(sf::Mouse::getPosition(window));
			
		world.update(dt);


		world.draw(window);
		ImGui::SFML::Render(window);
		window.draw(tDt);
		window.display();

		tExitFrame = getTimeStamp();
	}

	ImGui::SFML::Shutdown();
	return 0;
}