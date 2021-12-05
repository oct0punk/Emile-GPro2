
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

#include "imgui.h"
#include "imgui-SFML.h"

using namespace sf;

void Normalize(Vector2f* v) {
	float magnitude = sqrt((v->x * v->x) + (v->y * v->y));
	*v = Vector2f(v->x / magnitude, v->y / magnitude);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Asteroid");
	window.setFramerateLimit(60);

	World world;

	#pragma region player	
	float speed = 300.0f;
	ConvexShape* pShape = new ConvexShape(4);
	pShape->setPoint(0, Vector2f(0, 0));
	pShape->setPoint(1, Vector2f(80, 20));
	pShape->setPoint(2, Vector2f(0, 40));
	pShape->setPoint(3, Vector2f(20, 20));
	pShape->setOrigin(Vector2f(20, 20));
	pShape->setFillColor(Color::Transparent);
	pShape->setOutlineThickness(2);

	PlayerPad p(EType::Player, pShape);
	world.data.push_back(&p);
	#pragma endregion
	
	#pragma region Bullet
	float bWidth = 10.0f;
	float bHeight = 1.0f;
	RectangleShape* bShape = new RectangleShape(Vector2f(bWidth, bHeight));
	LaserShot laser(EType::Bullet, bShape);
	world.data.push_back(&laser);
	#pragma endregion

	

	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();


	ImGui::SFML::Init(window);
	sf::Clock deltaClock;
	sf::Color clearColor(20, 20, 20, 20);


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
			laser.create(pPos.x, pPos.y, pToMouse.x, pToMouse.y);
		}

		#pragma endregion

		{	using namespace ImGui;
		SFML::Update(window, deltaClock.restart());
		ShowDemoWindow();
		Begin("Edit");
		DragFloat("Speed", &speed, 1.0f, 0.0f, 1000.0f);
		Separator();
		if (DragFloat("Bullets width", &bWidth, .1f, 0.1f, 50.0f)) {
			bShape = new RectangleShape(Vector2f(bWidth, bHeight));
			laser.spr = bShape;
		}
		if (DragFloat("Bullets height", &bHeight, .1f, 0.1f, 50.0f)) {
			bShape = new RectangleShape(Vector2f(bWidth, bHeight));
			laser.spr = bShape;
		}
		DragFloat("Reload time", &laser.reloadTime, .05f, 0.0f, 1.0f);
		Separator();
		float col[4]{ clearColor.r / 255.0f, clearColor.g / 255.0f, clearColor.b / 255.0f, clearColor.a / 255.0f };
		if (ColorPicker4("ClearColor", col))
		{
			clearColor.r = col[0] * 255.f;
			clearColor.g = col[1] * 255.f;
			clearColor.b = col[2] * 255.f;
			clearColor.a = col[3] * 255.f;
		}

		ImGui::End();
		}	// ImGui

		world.update(dt);

		window.clear(clearColor);
		world.draw(window);		
		ImGui::SFML::Render(window);
		window.display();
		tExitFrame = getTimeStamp();
	}
	ImGui::SFML::Shutdown();

	return 0;
}