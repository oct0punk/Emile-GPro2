
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
#include "Game.h"

#include "imgui.h"
#include "imgui-SFML.h"

using namespace sf;



int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Asteroid");
	window.setFramerateLimit(60);

	World world(&window);
	Font font;
	font.loadFromFile("res/arial.ttf");
	Text text;
	text.setFont(font);


	#pragma region player	
	float speed = 800.0f;
	ConvexShape* pShape = new ConvexShape(10);
	pShape->setPoint(0, Vector2f(40, 0));
	pShape->setPoint(1, Vector2f(30, 10));
	pShape->setPoint(2, Vector2f(100, 15));
	pShape->setPoint(3, Vector2f(20, 20));
	pShape->setPoint(4, Vector2f(-10, 45));
	pShape->setPoint(5, Vector2f(-50, 0));
	pShape->setPoint(6, Vector2f(-10, -45));
	pShape->setPoint(7, Vector2f(20, -20));
	pShape->setPoint(8, Vector2f(100, -15));
	pShape->setPoint(9, Vector2f(30, -10));
	pShape->setFillColor(Color::Transparent);
	pShape->setOutlineThickness(4);

	PlayerPad p(pShape);
	world.data.push_back(&p);
	#pragma endregion
	
	#pragma region Bullet
	float bWidth = 50.0f;
	float bHeight = 2.0f;
	RectangleShape* bShape = new RectangleShape(Vector2f(bWidth, bHeight));
	Color bc = Color::Blue;
	Laser b(bShape, bc);
	world.data.push_back(&b);
	#pragma endregion

	#pragma region Wall
	int minRadius = 100;
	int maxRadius = 300;
	CircleShape* wShape = new CircleShape(minRadius + (rand() % (maxRadius - minRadius)));
	wShape->setOrigin(wShape->getRadius(), wShape->getRadius());
	Entity w(EType::Wall, wShape);
	w.setPosition(400, 400);
	world.data.push_back(&w);
	#pragma endregion

	#pragma region Enemy
	ConvexShape* eShape = new ConvexShape(4);
	eShape->setPoint(0, Vector2f(0, 0));
	eShape->setPoint(1, Vector2f(80, 20));
	eShape->setPoint(2, Vector2f(0, 40));
	eShape->setPoint(3, Vector2f(20, 20));
	eShape->setOrigin(Vector2f(20, 20));
	eShape->setFillColor(Color::Transparent);
	eShape->setOutlineThickness(3);
	Enemy e(eShape, bShape);
	e.p = &p;
	world.data.push_back(&e);
	#pragma endregion

	sf::RectangleShape rect(Vector2f(wShape->getGlobalBounds().width, wShape->getGlobalBounds().height));
	rect.setFillColor(Color::Transparent);
	rect.setOutlineThickness(1.0f);
	rect.setOutlineColor(Color::Green);

	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();


	ImGui::SFML::Init(window);
	sf::Clock deltaClock;
	sf::Color clearColor(20, 20, 20, 20);

	Game game(&world, &p);

	while (window.isOpen()) {
		sf::Event event;
		double dt = tExitFrame - tEnterFrame;
		tEnterFrame = getTimeStamp();
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}



		#pragma region PlayerControls
		// Move
		bool keyHit = false;
		Vector2f pPos = p.getPosition();
		if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Z)) {
			pPos.y -= speed * dt;
			keyHit = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {
			pPos.y += speed * dt;
			keyHit = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Q)) {
			pPos.x -= speed * dt;
			keyHit = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
			pPos.x += speed * dt;
			keyHit = true;
		}
		if (keyHit)
			p.setPosition(pPos.x, pPos.y);


		Vector2f pToMouse = Vector2f(
			Mouse::getPosition(window).x - p.getPosition().x,
			Mouse::getPosition(window).y - p.getPosition().y);
		Normalize(&pToMouse);
		float intoMouse = atan2(pToMouse.y, pToMouse.x) * RadToDeg();
		p.setRotation(intoMouse);

		// Shoot
		if (Mouse::isButtonPressed(Mouse::Left)) {
			b.create(pPos.x, pPos.y, pToMouse.x, pToMouse.y);
		}

#pragma endregion
		
		rect.setSize(Vector2f(pShape->getGlobalBounds().width, pShape->getGlobalBounds().height));
		rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
		rect.setPosition(p.getPosition());
		
		{	using namespace ImGui;
		SFML::Update(window, deltaClock.restart());
		ShowDemoWindow();
		Begin("Edit");
		DragFloat("Speed", &speed, 1.0f, 0.0f, 1000.0f);
		Separator();

		DragFloat("bSpeed", &b.speed, 5.0f, 100.0f, 10000.0f);
		if (DragFloat("bWidth", &bWidth, .1f, 0.1f, 50.0f)) {
			bShape = new RectangleShape(Vector2f(bWidth, bHeight));
			b.spr = bShape;
		}
		if (DragFloat("bHeight", &bHeight, .1f, 0.1f, 50.0f)) {
			bShape = new RectangleShape(Vector2f(bWidth, bHeight));
			b.spr = bShape;
		}
		DragFloat("Reload time", &b.reloadTime, .05f, 0.0f, 1.0f);
		Separator();

		//background color
		float col[4]{ clearColor.r / 255.0f, clearColor.g / 255.0f, clearColor.b / 255.0f, clearColor.a / 255.0f };
		if (ColorPicker4("ClearColor", col))
		{
			clearColor.r = col[0] * 255.f;
			clearColor.g = col[1] * 255.f;
			clearColor.b = col[2] * 255.f;
			clearColor.a = col[3] * 255.f;
		}

		ImGui::End();
		}

		world.update(dt);
		int count = 0;
		for (auto b : b.alive)
			if (b)
				count++;
		text.setString(to_string(count));

		window.clear(clearColor);
		world.draw(window);
		ImGui::SFML::Render(window);
		window.draw(rect);
		window.draw(text);
		window.display();
		tExitFrame = getTimeStamp();
	}
	ImGui::SFML::Shutdown();

	return 0;
}