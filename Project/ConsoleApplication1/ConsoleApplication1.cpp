
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


#pragma region Bullet
	float bWidth = 35.0f;
	float bHeight = 3.0f;
	RectangleShape* bShape = new RectangleShape(Vector2f(bWidth, bHeight));
	Color bc = Color::Blue;
	Laser b(bShape, bc);
	world.dataPlay.push_back(&b);
#pragma endregion


#pragma region player	
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
	pShape->setFillColor(Color::Blue);
	pShape->setOutlineColor(Color::Yellow);
	pShape->setOutlineThickness(7);

	PlayerPad p(pShape, &b);
	p.setPosition(950, 400);
	world.dataPlay.push_back(&p);
#pragma endregion


	Game::create(&world, &p);
	Audio::GetInstance();

	ImGui::SFML::Init(window);

	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();
	bool shootflag = true;

	int* thickness = new int(2);

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
		if (sf::Joystick::isConnected) {
			std::cout << "Joystick is connected\n";
			sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);
		}
		#pragma region PlayerControls
		if (Game::GetInstance()->state == GameState::Playing)
		{
			// Shoot
			Vector2f pPos = p.getPosition();
			Vector2f aimDir;
			if (sf::Joystick::isConnected(0)) {
				aimDir = Vector2f(
					sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::U),
					sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::V));
			}
			else {
				aimDir = Vector2f(
					Mouse::getPosition(window).x - p.getPosition().x,
					Mouse::getPosition(window).y - p.getPosition().y);
			}
			Normalize(&aimDir);
			float rotAngle = atan2(aimDir.y, aimDir.x) * RadToDeg();
			p.setRotation(rotAngle);

			// Shoot
			if (Mouse::isButtonPressed(Mouse::Left)) {
				if (world.timeScale < 1.0f) {
					if (shootflag) {
						b.create(pPos.x, pPos.y, aimDir.x, aimDir.y, world.timeScale * world.timeScale, 8);
						shootflag = false;
					}
				}
				else {
					b.create(pPos.x, pPos.y, aimDir.x, aimDir.y, 0.1f);
				}
			}
			else {
				shootflag = true;
			}

		}
		#pragma endregion
		
		cursor.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
		
		Game::GetInstance()->update(dt);
		text.setString(to_string(p.power));

		// IMGUI
		{	using namespace ImGui;
		ImGui::SFML::Update(window, sf::milliseconds((int)(dt * 1000.0)));
		ShowDemoWindow();
		Begin("Edit");
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