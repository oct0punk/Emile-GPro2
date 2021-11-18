
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Int64Array.hpp"
#include "Tool.hpp"
#include "List.hpp"
#include <algorithm>
#include <vector>
#include "Tree.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include "Curve.hpp"
#include "Bullet.hpp"
#include "Entity.h"
#include "World.h"

float catmull(float p0 , float p1 , float p2,float p3 , float t ) {
	auto q = 2.0f * p1;
	auto t2 = t * t;

	q += (-p0 + p2) * t;
	q += (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * t2;
	q += (-p0 + 3 * p1 - 3 * p2 + p3) * t2 * t;

	return 0.5f * q;
}

void drawMountain(sf::RenderWindow& window) {

	sf::VertexArray arr;
	arr.setPrimitiveType(sf::LineStrip);
	sf::Color col = sf::Color::Green;

	float baseline = 350;

	sf::Vector2f a(0, baseline+50);
	sf::Vector2f b(400, baseline-150);
	sf::Vector2f c(1100, baseline +32);
	sf::Vector2f d(window.getSize().x, baseline);
	col.a = 100;

	col = sf::Color::Magenta;
	for (int i = 0; i < 256; ++i) {
		float t = 1.0f * i / 256;
		float x = catmull(a.x, a.x, b.x, c.x, t);
		float y = catmull(a.y, a.y, b.y, c.y, t);
		arr.append(sf::Vertex(sf::Vector2f(x, y), col));
	}
	for (int i = 0; i < 256; ++i) {
		float t = 1.0f * i / 256;
		float x = catmull(a.x, b.x, c.x, d.x, t);
		float y = catmull(a.y, b.y, c.y, d.y, t);
		arr.append(sf::Vertex( sf::Vector2f(x,y), col));
	}

	for (int i = 0; i < 256; ++i) {
		float t = 1.0f * i / 256;
		float x = catmull(b.x, c.x, d.x, d.x, t);
		float y = catmull(b.y, c.y, d.y, d.y, t);
		arr.append(sf::Vertex(sf::Vector2f(x, y), col));
	}
	window.draw(arr);
}

void drawGround(sf::RenderWindow& window) {
	sf::VertexArray arr;
	arr.setPrimitiveType(sf::LineStrip);

	float baseline = window.getSize().y - 160;

	sf::Vector2f a(0, baseline);
	sf::Vector2f b(window.getSize().x, baseline);

	arr.append(sf::Vertex(a, sf::Color::Yellow));
	arr.append(sf::Vertex(b, sf::Color::Red));

	window.draw(arr);
}



int main()
{
	sf::RenderWindow window(sf::VideoMode(1240, 720), "SFML works!");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	
	World world;

	#pragma region Shapes
	sf::RectangleShape wall(sf::Vector2f(10, 4000));
	wall.setOrigin(10, 2000);
	wall.setFillColor(sf::Color::Green);
	wall.setOutlineColor(sf::Color::White);
	wall.setOutlineThickness(6);

	sf::RectangleShape* platform = new sf::RectangleShape(sf::Vector2f(300, 10));
	platform->setOrigin(sf::Vector2f(40, 8));
	platform->setFillColor(sf::Color::Cyan);
	platform->setOutlineThickness(5);

	sf::Texture brochet;
	if (!brochet.loadFromFile("res/brochet.png"))
		throw "pesson";
	sf::CircleShape* bullet = new sf::CircleShape(50);
	bullet->setOrigin(50, 50);
	bullet->setTexture(&brochet);
	bullet->setFillColor(sf::Color::Yellow);
	bullet->setOutlineColor(sf::Color::Red);
	bullet->setOutlineThickness(1);

	sf::Texture macron;
	if (!macron.loadFromFile("res/macron.jpg"))
		throw "nous sommes en guerre";

	int brickWidth = 80;
	sf::RectangleShape brick(sf::Vector2f(brickWidth, 30));
	brick.setOutlineColor(sf::Color(100, 0, 0));
	brick.setOutlineThickness(5);
	brick.setTexture(&macron);
#pragma endregion


	#pragma region Entity
	PlayerPad* player = new PlayerPad(EType::Player, platform);
	player->setPosition(640, window.getSize().y - 200);
	Entity* ball = new Entity(EType::Ball, bullet);
	player->currentBall = ball;
	ball->setPosition(window.getSize().x / 2, window.getSize().y / 2);
	ball->dx = 666;
	ball->dy = 300;
	Entity* leftSideBound = new Entity(EType::Wall, &wall);
	leftSideBound->setPosition(10, window.getSize().y / 2);
	Entity* rightSideBound = new Entity(EType::Wall, new sf::RectangleShape(wall));
	rightSideBound->setPosition(window.getSize().x - 10, window.getSize().y / 2);
	Entity* ceiling = new Entity(EType::Wall, new sf::RectangleShape(wall));
	ceiling->setRotation(-90);
	ceiling->setPosition(window.getSize().x / 2, 10);
	Entity* floor = new Entity(EType::Wall, new sf::RectangleShape(wall));
	floor->setRotation(-90);
	floor->setPosition(window.getSize().x / 2, window.getSize().y - 10);
	for (int i = 20; i < window.getSize().x - brickWidth; i += brickWidth + 20) {
		Entity* newBrick = new Entity(EType::Brick, new sf::RectangleShape(brick));
		newBrick->setPosition(i, 70);
		world.data.push_back(newBrick);
	}
	for (int i = 50; i < window.getSize().x - brickWidth; i += brickWidth + 20) {
		Entity* newBrick = new Entity(EType::Brick, new sf::RectangleShape(brick));
		newBrick->setPosition(i, 120);
		world.data.push_back(newBrick);
	}
	for (int i = 20; i < window.getSize().x - brickWidth; i += brickWidth + 20) {
		Entity* newBrick = new Entity(EType::Brick, new sf::RectangleShape(brick));
		newBrick->setPosition(i, 170);
		world.data.push_back(newBrick);
	}
	for (int i = 50; i < window.getSize().x - brickWidth; i += brickWidth + 20) {
		Entity* newBrick = new Entity(EType::Brick, new sf::RectangleShape(brick));
		newBrick->setPosition(i, 220);
		world.data.push_back(newBrick);
	}

	world.data.push_back(player);
	world.data.push_back(ball);
	world.data.push_back(leftSideBound);
	world.data.push_back(rightSideBound);
	world.data.push_back(ceiling);
	world.data.push_back(floor);
#pragma endregion

	sf::Font fArial;
	if (!fArial.loadFromFile("res/arial.ttf"))	
		cout << "font not loaded" << endl;
	sf::Text tDt;
	tDt.setFont(fArial);
	tDt.setFillColor(sf::Color::White);
	tDt.setCharacterSize(45);
	tDt.setPosition(sf::Vector2f(20, window.getSize().y - 150));

	sf::Texture texture;
	if (!texture.loadFromFile("res/clouds.jpg"))
		throw "noJPG";

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(2.0f, 2.0f);
	sprite.setColor(sf::Color(50, 50, 50));

	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();

	
	float radToDeg = 57.2958;

	while (window.isOpen()){
		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

		sf::Event event;
		double dt = tExitFrame - tEnterFrame;
		tEnterFrame = getTimeStamp();
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}

		#pragma region Player Movement
		sf::Vector2f move;
		float deltaX = dt * 1000;
		float deltaY = dt * 1000;
		bool keyHit = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			move.x -= deltaX;
			keyHit = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			move.x += deltaX;
			keyHit = true;
		}
		if (keyHit) {
			auto vec = player->getPosition() + sf::Vector2f(move.x, move.y);
			if (vec.x < 0)
				vec.x = 0;
			else if (vec.x > window.getSize().x)
				vec.x = window.getSize().x;
			player->setPosition(vec.x, vec.y);
		}
#pragma endregion

		tDt.setString( to_string(dt)+" FPS:"+ to_string((int)(1.0f / dt)) + "\nNous sommes en guerre");
		world.update(dt);

		window.clear(sf::Color(20, 20, 20));
		window.draw(sprite);

		window.draw(tDt);
		world.draw(window);
		drawGround(window);
		
		window.display();

		tExitFrame = getTimeStamp();
	}

	return 0;
}