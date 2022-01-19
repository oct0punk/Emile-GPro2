
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <optional>
#include <algorithm>
#include <sys/stat.h>

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "imgui.h"

#include "Tool.hpp"

#include "Curve.hpp"
#include "Particle.hpp"
#include "Entity.hpp"
#include "Game.hpp"


int main() {
	sf::RenderWindow window(sf::VideoMode(Game::W, Game::H), "SFML works!");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	sf::Font fArial;
	if (!fArial.loadFromFile("res/arial.ttf"))
		cout << "font not loaded" << endl;
	sf::Text tDt;
	tDt.setFont(fArial);
	tDt.setFillColor(sf::Color::White);
	tDt.setCharacterSize(45);

	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();

	bool mouseLeftWasPressed = false;
	double timer = 0.0;

	ImGui::SFML::Init(window);

	sf::Vector2i winPos = window.getPosition();

	sf::RectangleShape* spr = new sf::RectangleShape(sf::Vector2f(12, 28));
	spr->setFillColor(sf::Color::Red);
	spr->setOutlineColor(sf::Color::Green);
	spr->setOutlineThickness(4);
	spr->setOrigin(spr->getSize().x * 0.5, spr->getSize().y);
	Game::init();
	Game::player = new Entity(spr, Game::W / Entity::stride * 0.5, lround(Game::H / Entity::stride) - 2);

	if (!sf::Shader::isAvailable()) {
		cout << "shaders are not supported\n";
		return 1;
	}

	sf::Shader shader;
	if (!shader.loadFromFile("res/VtxShader.txt", "res/FrgtShader.txt")) {
		std::cout << "no shader";
		return 1;
	}
	sf::Glsl::Vec4 transCol(1.0f, 1.0f, 1.0f, 1.0f);
	sf::Glsl::Vec4 mulCol(1.0f, 1.0f, 1.0f, 1.0f);
	sf::Glsl::Vec4 addCol(0.0f, 0.0f, 0.0f, 1.0f);

	sf::RectangleShape shaderShape(sf::Vector2f(120, 72));
	sf::Texture bg;
	bg.loadFromFile("res/bg.jpg");
	shaderShape.setTexture(&bg);
	shader.setUniform("texture", sf::Shader::CurrentTexture);

	sf::Glsl::Vec4 matrix{ 0.0f, 0.0f, 0.0f, 0.0f };
	double time = 0.0;

	while (window.isOpen()) {
		sf::Event event;

		double dt = tExitFrame - tEnterFrame;
		tEnterFrame = getTimeStamp();

		bool mouseLeftIsPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		bool mouseIsReleased = (!mouseLeftIsPressed && mouseLeftWasPressed);
		bool shifIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(window, event);

			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();

			if (event.type == sf::Event::MouseButtonPressed) {

				if (shifIsPressed) {
					auto cx = event.mouseButton.x / Entity::stride;
					auto cy = event.mouseButton.y / Entity::stride;

					auto& p = Game::currentPath;
					Game::currentPath.clear();
					sf::Vector2i start = sf::Vector2i(Game::player->cx, Game::player->cy);
					sf::Vector2i end = sf::Vector2i(cx, cy);

					sf::Vector2i cur = end;
					Game::currentPath.push_back(end);
					while (cur != start) {
						auto pos = Game::dij.pred.find(cur);
						if (pos != Game::dij.pred.end()) {
							cur = Game::dij.pred[cur];
							Game::currentPath.push_back(cur);
						}
						else {
							Game::currentPath.clear();
							break;
						}
					}
					std::reverse(p.begin(), p.end());
					Game::player->curPath = p;
				}
				else {
					auto cx = event.mouseButton.x / Entity::stride;
					auto cy = event.mouseButton.y / Entity::stride;

					int pos = -1;
					int idx = 0;
					for (auto& v : Game::walls) {
						if (v.x == cx && v.y == cy)
							pos = idx;
						idx++;
					}

					if (pos < 0)
						Game::walls.push_back(sf::Vector2i(cx, cy));
					else
						Game::walls.erase(Game::walls.begin() + pos);
				}
			}

			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Enter) {
					Game::dij.compute(sf::Vector2i(Game::player->cx, Game::player->cy));
				}
			}
		}


		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

		if (mouseLeftIsPressed && !mouseLeftWasPressed) {

		}

		auto player = Game::player;
		float max_speed = 10;

		static bool wasPressedUp = false;



		if (mouseLeftIsPressed)
			mouseLeftWasPressed = true;
		else
			mouseLeftWasPressed = false;

		////////////////////

		//CLEAR
		window.clear(sf::Color::Black);

		////////////////////
		//UPDATE
		auto dtms = ((int)(dt * 1000.0));
		auto ms = sf::milliseconds(dtms == 0 ? 1 : dtms);
		ImGui::SFML::Update(window, ms);

		ImGui::Begin("Shader"); 
		float colTrans[4] = { transCol.x, transCol.y, transCol.z, transCol.w };
		if (ImGui::ColorPicker4("Transmission", colTrans)) {
			transCol.x = colTrans[0] / 255.0f;
			transCol.y = colTrans[1] / 255.0f;
			transCol.z = colTrans[2] / 255.0f;
			transCol.w = colTrans[3] / 255.0f;
		}
		float colAdd[4] = { addCol.x, addCol.y, addCol.z, addCol.w};
		if (ImGui::ColorPicker4("AddCol", colAdd)) {
			addCol.x = colAdd[0];
			addCol.y = colAdd[1];
			addCol.z = colAdd[2];
			addCol.w = colAdd[3];
		}
		float colMul[4] = { mulCol.x, mulCol.y, mulCol.z, mulCol.w};
		if (ImGui::ColorPicker4("MulCol", colMul)) {
			mulCol.x = colMul[0];
			mulCol.y = colMul[1];
			mulCol.z = colMul[2];
			mulCol.w = colMul[3];
		}
		ImGui::NewLine();

		ImGui::End();

		time += dt;
		//matrix.x = (.5f + .5f * sin(time)) * 1240;
		//matrix.y = (.5f + .5f * cos(time)) * 720 ;
		matrix.x = (1 + sin(time)) * 1240;
		matrix.y = (1 + cos(time)) * 720;
		matrix.w = 1.0f;

		shader.setUniform("mulCol", mulCol);
		shader.setUniform("addCol", addCol);
		shader.setUniform("transCol", transCol);
		shader.setUniform("matrix", matrix);

		Game::im();

		Game::update(dt);
		Game::parts.update(dt);


		////////////////////
		//DRAW

		Game::parts.draw(window);
		Game::render(window);
		window.draw(tDt);

		window.draw(shaderShape, &shader);

		/*
		if (Game::shake > 0)
			window.setPosition(winPos + sf::Vector2i(0 + rand() % 5, 0 + rand() % 5));
		else
			window.setPosition(winPos);
		Game::shake--;
		*/
		ImGui::SFML::Render(window);
		window.display();
		tExitFrame = getTimeStamp();

		timer += dt;
	}

	return 0;
}