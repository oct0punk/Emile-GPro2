
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
	world.gridSize = 16;

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

	Entity g(ground, 400, 700, world.gridSize);
	Entity p(rect, 400, 400, world.gridSize);
	p.simulated = false;
	g.simulated = false;

	world.data.push_back(&p);
	world.data.push_back(&g);

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

		//float col[4]{ clearColor.r / 255.0f, clearColor.g / 255.0f, clearColor.b / 255.0f, clearColor.a / 255.0f };
		//if (ColorPicker4("ClearColor", col))
		//{
		//	clearColor.r = col[0] * 255.f;
		//	clearColor.g = col[1] * 255.f;
		//	clearColor.b = col[2] * 255.f;
		//	clearColor.a = col[3] * 255.f;
		//}
		ImGui::Value("cx", p.cx); ImGui::SameLine();
		ImGui::Value("cy", p.cy);
		ImGui::Value("rx", p.rx); ImGui::SameLine();
		ImGui::Value("ry", p.ry);
		ImGui::Value("acceleration", p.dy);
		ImGui::DragFloat("Speed", &speed, 0.01f, 0.0f, 100.0f, "%f", 1);
		ImGui::DragInt("GridSize", &p.gridSize , 1, 1, 2000, "%i", 1);
		
		float x = p.getPosition().x;
		float y = p.getPosition().y;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			x -= 1.1f * speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			x += 1.1f * speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			y -= 1.1f * speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			y += 1.1f * speed;

		p.cx = x;
		p.cy = y;

		ImGui::End();
		world.update(dt);


		window.clear(sf::Color::Black);
		ImGui::SFML::Render(window);
		window.draw(tDt);
		world.draw(window);
		window.display();

		tExitFrame = getTimeStamp();
	}

	ImGui::SFML::Shutdown();
	return 0;
}