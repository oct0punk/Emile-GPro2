#pragma once
#include "SFML/Graphics/Transform.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RenderTexture.hpp"

enum CmdType {
	Clear,
	Advance,
	Rotate,
	PenUp,
	PenDown,
	PenColor,
};

struct Cmd {
	CmdType				type = Advance;
	float				maxDuration = 0.333f;
	float				timer = 0.0f;
	float				value = 0.0f;
	float				originalValue = 0.0f;
	sf::Color			col;
	Cmd* next = nullptr;

	Cmd(CmdType t, float _value = 0.0) {
		type = t;
		value = _value;
		originalValue = value;
	};

	Cmd* append(Cmd* nu) {
		if (next == nullptr)
			next = nu;
		else
			next = next->append(nu);
		return this;
	};

	Cmd* popFirst() {
		Cmd* nu = next;
		delete this;
		return nu;
	};
};

class Turtle {
public:
	sf::CircleShape		comps[4];
	sf::RectangleShape	dir;
	sf::RenderTexture	rt;

	bool penEnabled = false;
	sf::Color penColor;

	Turtle(int n) {
		sf::Texture shellTexture;		
		if (!shellTexture.loadFromFile("res/shellTexture.jpg"))
			throw "noTexture";
		shellTexture.setSmooth(true);
		
		auto &carapace = comps[1];
		carapace = sf::CircleShape(60);
		carapace.setTexture(&shellTexture);

		auto& head = comps[0];
		head = sf::CircleShape(20);
		head.setFillColor(sf::Color(100, 0, 0));
		
		auto& leftEye = comps[2];
		leftEye = sf::CircleShape(2);
		
		auto& rightEye = comps[3];
		rightEye = sf::CircleShape(2);

		head.setOrigin(20, 90);
		carapace.setOrigin(60, 60);
		leftEye.setOrigin(4, 80);
		rightEye.setOrigin(-4, 80);

		rt.create(2048, 2048);
		rt.clear(sf::Color(0, 0, 0, 0));

		trs.translate(400, 400);
	}

	void reset() {
		trs = sf::Transform::Identity;
		trs.translate(200, 200);
		trs.rotate(180);
		rt.clear(sf::Color(0, 0, 0, 0));

		while (cmds) {
			cmds = cmds->popFirst();
		}
	}
	
	void update(double dt) {

		if (cmds)
			cmds = applyCmdInterp(cmds, dt);
	}

	void draw(sf::RenderWindow& win){
		for (auto& c : comps)
			win.draw(c, trs);
		win.draw(dir, trs);

		rt.display();

		sf::Sprite s;
		s.setTexture(rt.getTexture());
		win.draw(s);
	}

	//ajoute les cmds a la fin de la liste courante
	void appendCmd(Cmd* cmd) {
		if (cmds)
			cmds = cmds->append(cmd);
		else
			cmds = cmd;
	}

	void write(FILE* f, Cmd* cmd) {
		switch (cmd->type) {
		case Clear: { fprintf(f, "Clear\n"); break; }
		case Advance: { fprintf(f, "Advance %d\n", (int)cmd->value); break; }
		case Rotate: { fprintf(f, "Rotate %d\n", (int)cmd->value); break; }
		case PenUp: { fprintf(f, "PenUp\n"); break; }
		case PenDown: { fprintf(f, "PenDown\n"); break; }
		case PenColor: { fprintf(f, "PenColor %u\n", (unsigned int)cmd->col.toInteger()); break; }
		}
		if (cmd->next)
			write(f, cmd->next);
	}

	void translate(float value) { appendCmd(new Cmd(Advance, value)); };

	void rotate(float value) { appendCmd(new Cmd(Rotate, value)); };

	void setPen(bool value) {
		if (value)
			appendCmd(new Cmd(PenDown));
		else
			appendCmd(new Cmd(PenUp));
	};

	void setPenColor(sf::Color col) {
		auto colCmd = new Cmd(PenColor);
		colCmd->col = col;
		appendCmd(colCmd);
	};

	void writeCommands(const char* fname) {
		FILE* f = nullptr;
		fopen_s(&f, fname, "wb");
		if (f) {
			write(f, cmds);
			fflush(f);
			fclose(f);
		}
	}

	sf::Vector2f getPosition() { return trs.transformPoint(sf::Vector2f()); };

	Cmd* cmds = nullptr;

protected:
	sf::Transform		trs;
	Cmd* applyCmd(Cmd* cmd) {
		switch (cmd->type) {
		case Clear:
			reset();
			break;
		case Advance:
			trs.translate(0, -cmd->value);
			if (penEnabled) {
				sf::CircleShape pen(8);
				pen.setFillColor(penColor);
				pen.setOrigin(8, 8);
				pen.setPosition(trs.transformPoint(sf::Vector2f(0, 0)));
				rt.draw(pen);
			}
			break;
		case Rotate:	trs.rotate(cmd->value); break;
		case PenUp:		penEnabled = false; break;
		case PenDown:	penEnabled = true; break;
		case PenColor:
			penColor = cmd->col;
			break;
		default:
			break;
		}

		return nullptr;
	}
	Cmd* applyCmdInterp(Cmd* cmd, double dt) {
		dt = 1.0f / 60.0f * 0.1;
		float ratio = cmd->timer / cmd->maxDuration;
		float speed = 1.0f / cmd->maxDuration;
		bool destroy = false;
		switch (cmd->type) {
		case Clear:
			destroy = true;
			break;
		case Advance:
			trs.translate(0, -cmd->value * dt * speed);
			if (penEnabled) {
				sf::CircleShape pen(8);
				pen.setFillColor(penColor);
				pen.setOrigin(8, 8);
				pen.setPosition(trs.transformPoint(sf::Vector2f(0, 0)));
				rt.draw(pen);
			}
			break;
		case Rotate:
			trs.rotate(cmd->value * dt * speed);
			break;
		case PenUp:		penEnabled = false;
			destroy = true;
			break;
		case PenDown:	penEnabled = true;
			destroy = true;
			break;
		case PenColor:
			penColor = cmd->col;
			destroy = true;
			break;
		default:
			destroy = true;
			break;
		}

		cmd->timer += dt;
		if (cmd->timer >= cmd->maxDuration)
			destroy = true;

		if (!destroy) {
			return cmd;
		}
		else {
			cmd = cmd->popFirst();
			return cmd;
		}
	}
};