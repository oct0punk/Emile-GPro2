
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
#include "Audio.h"

#include "imgui.h"
#include "imgui-SFML.h"

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(1820, 950), "Astro Neon");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	World world(&window);
	Font font;
	font.loadFromFile("res/arial.ttf");
	Text text;
	text.setFont(font);


	// Target cursor
	CircleShape cursor(20);
	cursor.setFillColor(Color::Red);
	cursor.setOrigin(20, 20);
	sf:Texture target;
	target.loadFromFile("res/target.png");
	cursor.setTexture(&target);
	window.setMouseCursorVisible(false);



#pragma region player	
	float speed = 800.0f;
	ConvexShape* pShape = new ConvexShape(11);
	pShape->setPoint(0, Vector2f(30, 0));						  /*		7 ----- 8				  */
	pShape->setPoint(1, Vector2f(13, 30));						  /*	  /				    	9	  */
	pShape->setPoint(2, Vector2f(60, 35));						  /*	 /				10			  */
	pShape->setPoint(3, Vector2f(18, 55));						  /*	6				  \			  */
	pShape->setPoint(4, Vector2f(-20, 30));						  /* 	|				   \		  */
	pShape->setPoint(5, Vector2f(-45, 20));						  /*	|		 X			0		  */
	pShape->setPoint(6, Vector2f(-45, -20));					  /*	5				  /			  */
	pShape->setPoint(7, Vector2f(-20, -30));					  /*	 \				 1			  */
	pShape->setPoint(8, Vector2f(18, -55));						  /*	  \						2	  */
	pShape->setPoint(9, Vector2f(60, -35));						  /*		4 ----- 3				  */
	pShape->setPoint(10, Vector2f(13, -30));			
	pShape->setFillColor(Color::Transparent);			
	pShape->setOutlineThickness(4);

	PlayerPad p(pShape);
	p.setPosition(950, 400);
	world.dataPlay.push_back(&p);
#pragma endregion

#pragma region Bullet
	float bWidth = 35.0f;
	float bHeight = 3.0f;
	RectangleShape* bShape = new RectangleShape(Vector2f(bWidth, bHeight));
	Color bc = Color::Blue;
	Laser b(bShape, bc);
	world.dataPlay.push_back(&b);
#pragma endregion

	world.SpawnObstacle(100);
	Game::create(&world);
	Audio::GetInstance();

	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();


	ImGui::SFML::Init(window);
	sf::Clock deltaClock;
	world.clearColor = new Color(20, 20, 20, 20);


	while (window.isOpen()) {
		double dt = tExitFrame - tEnterFrame;
		tEnterFrame = getTimeStamp();
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}


		// UPDATE
		#pragma region PlayerControls
		// Move
		if (p.visible)
		{
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

		}
		#pragma endregion
		
		cursor.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

		

		Game::GetInstance()->update(dt);
		text.setString(to_string(world.eCount));

		// IMGUI
		{	using namespace ImGui;
		ImGui::SFML::Update(window, sf::milliseconds((int)(dt * 1000.0)));
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
		DragFloat("Reload time", &b.reloadTime, .01f, 0.01f, .5f);
		Separator();

		//background color
		float col[4]{ world.clearColor->r / 255.0f, world.clearColor->g / 255.0f, world.clearColor->b / 255.0f, world.clearColor->a / 255.0f };
		if (ColorPicker4("ClearColor", col))
		{
			world.clearColor->r = col[0] * 255.f;
			world.clearColor->g = col[1] * 255.f;
			world.clearColor->b = col[2] * 255.f;
			world.clearColor->a = col[3] * 255.f;
		}
		ImGui::End();
		}


		// RENDERING
		Game::GetInstance()->draw(window);
		window.draw(text);
		window.draw(cursor);
		ImGui::SFML::Render(window);
		window.display();
		tExitFrame = getTimeStamp();
	}
	ImGui::SFML::Shutdown();

	return 0;
}