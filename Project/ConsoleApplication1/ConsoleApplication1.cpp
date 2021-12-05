
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

Vector2f Reflect(Vector2f incident, Vector2f normal) {
	// => For a given incident vector I and surface normal N reflect returns the reflection direction calculated as I - 2.0 * dot(N, I) * N.
	float x = incident.x - 2.0f * DotProduct(normal, incident) * normal.x;
	float y = incident.y - 2.0f * DotProduct(normal, incident) * normal.y;
	return Vector2f(x, y);
}

float DotProduct(Vector2f u, Vector2f v) {
	float uNorm = sqrt(u.x * u.x + u.y * u.y);
	float vNorm = sqrt(v.x * v.x + v.y * v.y);
	return uNorm * vNorm * cos(atan2(0, u.x) - atan2(0, v.x));
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

	sf::RectangleShape rect(Vector2f(pShape->getGlobalBounds().width, pShape->getGlobalBounds().height));
	rect.setFillColor(Color::Transparent);
	rect.setOutlineThickness(1.0f);
	rect.setOutlineColor(Color::Green);

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
		rect.setSize(Vector2f(pShape->getGlobalBounds().width * 0.8f, pShape->getGlobalBounds().height * 0.8f));
		rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
		rect.setPosition(p.getPosition());
		{	using namespace ImGui;
		SFML::Update(window, deltaClock.restart());
		ShowDemoWindow();
		Begin("Edit");
		DragFloat("Speed", &speed, 1.0f, 0.0f, 1000.0f);
		Separator();

		if (DragFloat("bWidth", &bWidth, .1f, 0.1f, 50.0f)) {
			bShape = new RectangleShape(Vector2f(bWidth, bHeight));
			laser.spr = bShape;
		}
		if (DragFloat("bHeight", &bHeight, .1f, 0.1f, 50.0f)) {
			bShape = new RectangleShape(Vector2f(bWidth, bHeight));
			laser.spr = bShape;
		}
		DragFloat("Reload time", &laser.reloadTime, .05f, 0.0f, 1.0f);
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

		window.clear(clearColor);
		world.draw(window);
		ImGui::SFML::Render(window);
		window.draw(rect);
		window.display();
		tExitFrame = getTimeStamp();
	}
	ImGui::SFML::Shutdown();

	return 0;
}