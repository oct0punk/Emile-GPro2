
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
int main()
{
	RenderWindow window(VideoMode(1240, 720), "Turtle");
	window.setFramerateLimit(60);
	World world;


	Font fArial;
	if (!fArial.loadFromFile("res/arial.ttf"))
		cout << "font not loaded" << endl;
	Text tDt;
	tDt.setFont(fArial);
	tDt.setFillColor(Color::White);
	tDt.setCharacterSize(45);

	ConvexShape* pShape = new ConvexShape(4);
	pShape->setPoint(1, Vector2f(45, 10));
	pShape->setPoint(0, Vector2f(0, 0));
	pShape->setPoint(2, Vector2f(0, 40));
	pShape->setPoint(3, Vector2f(10, 10));
	pShape->setFillColor(Color::Transparent);
	pShape->setOutlineColor(Color::White);
	pShape->setOutlineThickness(5);

	PlayerPad p(EType::Player, pShape);
	p.setPosition(400, 400);
	world.data.push_back(&p);

	double tStart = getTimeStamp();
	double tEnterFrame = getTimeStamp();
	double tExitFrame = getTimeStamp();


	ImGui::SFML::Init(window);
	Clock deltaClock;
	Color clearColor(20, 20, 20, 20);

	while (window.isOpen()) {
		Event event;
		double dt = tExitFrame - tEnterFrame;
		tDt.setString(to_string(dt) + " FPS:" + to_string((int)(1.0f / dt)));
		tEnterFrame = getTimeStamp();

		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
				window.close();
		}
		{	using namespace ImGui;
		SFML::Update(window, deltaClock.restart());
		ShowDemoWindow();
		Begin("Commands");
		float col[4]{ clearColor.r / 255.0f, clearColor.g / 255.0f, clearColor.b / 255.0f, clearColor.a / 255.0f };
		if (ColorPicker4("ClearColor", col))
		{
			clearColor.r = col[0] * 255.f;
			clearColor.g = col[1] * 255.f;
			clearColor.b = col[2] * 255.f;
			clearColor.a = col[3] * 255.f;
		}
		SameLine();
		//if (Button("Run")) {	// Appliquer head à turtle avec turtle.cmds
		//	if (head)turtle.appendCmd(head);
		//	head = nullptr;
		//}
		//SameLine();
		//if (Button("Load")) { // Lecture d'une list écrite dans un .txt
		//	FILE* f = nullptr;
		//	fopen_s(&f, "res/manualsave.txt", "rb");
		//	if (f && !feof(f)) {
		//		const int maxLineSize = 256;
		//		char line[maxLineSize] = {};
		//		for (;;) {
		//			int64_t nb = 0;
		//			fscanf_s(f, "%s %lld\n", line, maxLineSize, &nb);
		//			std::string s = line;
		//			if (s == "Advance") {
		//				turtle.translate(nb);
		//			}
		//			else if (s == "Rotate") {
		//				turtle.rotate(nb);
		//			}
		//			else if (s == "PenUp") {
		//				turtle.setPen(false);
		//			}
		//			else if (s == "PenDown") {
		//				turtle.setPen(true);
		//			}
		//			else if (s == "PenColor") {
		//				turtle.setPenColor(Color((unsigned int)nb));
		//			}
		//			else if (s == "Clear") {
		//				turtle.appendCmd(new Cmd(Clear));
		//			}
		//			if (feof(f))
		//				break;
		//		}
		//		fclose(f);
		//		head = turtle.cmds;
		//		turtle.cmds = nullptr;
		//	}
		//}
		//SameLine();
		//if (Button("Save")) { // Ecriture de la list dans un .txt
		//	FILE* f = nullptr;
		//	fopen_s(&f, "res/manualsave.txt", "wb");
		//	if (f && head) {
		//		turtle.write(f, head);
		//		fflush(f);
		//		fclose(f);
		//	}
		//}
		ImGui::End();
		}

		Vector2f pToMouse = (Vector2f)Mouse::getPosition(window) - p.getPosition();
		float intoMouse = atan2(pToMouse.y, pToMouse.x) * Rad2Deg();
		p.setRotation(intoMouse);

		world.update(dt);


		ImGui::SFML::Render(window);
		window.clear(clearColor);
		window.draw(tDt);
		world.draw(window);
		window.display();

		tExitFrame = getTimeStamp();
	}

	ImGui::SFML::Shutdown();
	return 0;
}