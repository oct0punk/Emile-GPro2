
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


	sf::Font fArial;
	if (!fArial.loadFromFile("res/arial.ttf"))
		cout << "font not loaded" << endl;
	sf::Text tDt;
	tDt.setFont(fArial);
	tDt.setFillColor(sf::Color::White);
	tDt.setCharacterSize(45);

	Turtle turtle(0);


	double tStart		= getTimeStamp();
	double tEnterFrame	= getTimeStamp();
	double tExitFrame	= getTimeStamp();
	float radToDeg = 57.2958f;


	ImGui::SFML::Init(window);
	sf::Clock deltaClock;
	int angle = 0;
	sf::Color clearColor(20, 20, 20, 20);
	sf::Color penColor(20, 20, 20, 20);

	while (window.isOpen()) {
		sf::Event event;
		double dt = tExitFrame - tEnterFrame;
		tEnterFrame = getTimeStamp();
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}
		ImGui::SFML::Update(window, deltaClock.restart());
		ImGui::ShowDemoWindow();


		{ using namespace ImGui;
			Begin("Commands");
			if (Button("Move BackWard"))
				turtle.translate(-100);
			SameLine();
			if (Button("Move Forward"))
				turtle.translate(100);

			if (Button("Turn")) {
				turtle.rotate(angle);
			} SameLine();
			InputInt("", &angle);		

			NewLine();
			Checkbox("Pen", &turtle.penEnabled);

			float penCol[4]{ penColor.r / 255.0f, penColor.g / 255.0f, penColor.b / 255.0f, penColor.a / 255.0f };
			if (ColorPicker4("Pen Color", penCol))
			{
				penColor.r = penCol[0] * 255.f;
				penColor.g = penCol[1] * 255.f;
				penColor.b = penCol[2] * 255.f;
				penColor.a = penCol[3] * 255.f;
				turtle.setPenColor(sf::Color(penColor.r, penColor.g, penColor.b, penColor.a));
			}
			
			NewLine();
			Separator();
			NewLine();

			float col[4]{ clearColor.r / 255.0f, clearColor.g / 255.0f, clearColor.b / 255.0f, clearColor.a / 255.0f };
			if (ColorPicker4("ClearColor", col))
			{
				clearColor.r = col[0] * 255.f;
				clearColor.g = col[1] * 255.f;
				clearColor.b = col[2] * 255.f;
				clearColor.a = col[3] * 255.f;
			}

			static Cmd* head = nullptr;
			//
			if (TreeNode("Commands")) {
				if (Button("+")) {
					auto p = new Cmd(Advance);
					p->value = p->originalValue = 50;
					if (nullptr == head)
						head = p;
					else
						head = head->append(p);
				}

				int idx = 0;
				auto h = head;
				while (h) {
					PushID(idx);
					Value("idx", idx);
					static const char* cmdTypes[]{
						"Clear",
						"Advance",
						"Rotate",
						"PenUp",
						"PenDown",
						"PenColor"
					};

					if (Combo("Cmd type", (int*)&h->type, cmdTypes, IM_ARRAYSIZE(cmdTypes))) {
						if (h->type == Rotate)
							h->value = h->originalValue = 0;
					}
					Value("timer", h->timer);
					switch (h->type)
					{
					case CmdType::Clear:
						break;
					case PenDown:
						break;
					case PenUp:
						break;
					case PenColor: {
						auto& col = h->col;
						float fcol[4] = { col.r / 255.0f, col.g / 255.0f, col.b / 255.0f, col.a / 255.0f };
						if (ImGui::ColorEdit4("col", fcol)) {
							col.r = fcol[0] * 255.0f;
							col.g = fcol[1] * 255.0f;
							col.b = fcol[2] * 255.0f;
							col.a = fcol[3] * 255.0f;
						}
						break;
					}
					case Rotate: {
						float degToRad = 0.0174533;
						float deg = h->originalValue * degToRad;
						if (SliderAngle("value", &deg)) {
							h->value = h->originalValue = deg / degToRad;
						}
						break;
					}
					default:
						if (DragFloat("value", &h->originalValue)) {
							h->value = h->originalValue;
						}
						break;
					}
					NewLine();
					ImGui::Separator();
					h = h->next;
					idx++;
					PopID();
				}
				Separator();
				Cmd* tc = turtle.cmds;
				idx = 0;
				while (tc) {
					PushID(idx);
					Value("val", tc->value);
					tc = tc->next;
					idx++;
					PopID();
				}

				SameLine();
				if (Button("Run")) {
					if (head)turtle.appendCmd(head);
					head = nullptr;
					//passer le head a la tortues
				}
				SameLine();
				if (Button("Load")) {
					FILE* f = nullptr;
					fopen_s(&f, "res/manualsave.txt", "rb");
					if (f && !feof(f)) {
						const int maxLineSize = 256;
						char line[maxLineSize] = {};
						for (;;) {
							int64_t nb = 0;
							fscanf_s(f, "%s %lld\n", line, maxLineSize, &nb);
							std::string s = line;
							if (s == "Advance") {
								turtle.translate(nb);
							}
							else if (s == "Rotate") {
								turtle.rotate(nb);
							}
							else if (s == "PenUp") {
								turtle.setPen(false);
							}
							else if (s == "PenDown") {
								turtle.setPen(true);
							}
							else if (s == "PenColor") {
								turtle.setPenColor(sf::Color((unsigned int)nb));
							}
							else if (s == "Clear") {
								turtle.appendCmd(new Cmd(Clear));
							}
							if (feof(f))
								break;
						}
						fclose(f);
						head = turtle.cmds;
						turtle.cmds = nullptr;
					}
				}
				SameLine();

				if (Button("Save")) {
					//sauver le fichier
					FILE* f = nullptr;
					fopen_s(&f, "res/manualsave.txt", "wb");
					if (f && head) {
						turtle.write(f, head);
						fflush(f);
						fclose(f);
					}
				}
				TreePop();
			}
			ImGui::End();
		}
		turtle.update(dt);
		

		tDt.setString(to_string(dt) + " FPS:" + to_string((int)(1.0f / dt)));
		world.update(dt);

		window.clear(clearColor);
		window.draw(tDt);
		turtle.draw(window);
		ImGui::SFML::Render(window);
		window.display();

		tExitFrame = getTimeStamp();
	}
	ImGui::SFML::Shutdown();

	return 0;
}