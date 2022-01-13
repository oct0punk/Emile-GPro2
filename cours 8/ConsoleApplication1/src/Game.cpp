#include "Game.hpp"
#include "Entity.hpp"
#include "imgui.h"
#include "SFML/Graphics/RectangleShape.hpp"
Dijkstra Game::dij;

Particle Game::parts;
int Game::shake = 0;
Entity * Game::player= nullptr;
std::vector<sf::Vector2i> Game::walls;

void Game::particlesAt(sf::Vector2f pos) {
	int flip = (rand() % 2 == 0) ? 1 : -1;
	parts.create(pos.x, pos.y, flip * rand() % 200, - (rand() % 80) - 35);
}

void Game::init() {
	walls.push_back(sf::Vector2i(5, 5));
}

void Game::im() {
	using namespace ImGui;
	static bool imOpened = true;
	if (Begin("Game", &imOpened)) {
		if (player) player->im();

	}
	End();
}
void Game::update(double dt) {
	if (player) player->update(dt);
}

void Game::render(sf::RenderWindow& win) {
	sf::RectangleShape rs(sf::Vector2f(Entity::stride, Entity::stride));
	rs.setOutlineThickness(2);
	rs.setFillColor(sf::Color(100, 100, 100));
	rs.setOutlineColor(sf::Color::Green);
	for (auto& v : walls) {
		rs.setPosition(v.x * Entity::stride, v.y * Entity::stride);
		win.draw(rs);
	}

	if(player) player->draw(win);

	sf::RectangleShape block(sf::Vector2f(1, 1));
	block.setFillColor(sf::Color::Red);
	for (auto z : dij.g) {
		block.setPosition(sf::Vector2f(z.first.x * Entity::stride, z.first.y * Entity::stride));
		win.draw(block);
	}

}

bool Game::isColliding(int ccx, int ccy) {
	if (ccx < 0)
		return true;
	if (ccy < 0)
		return true;

	if (ccx >= 1280 / Entity::stride)
		return true;

	if (ccy >= 720 / Entity::stride)
		return true;

	for (auto& vi : walls)
		if ((vi.x == ccx) && (vi.y == ccy))
			return true;
	
	return false;
}

float clamp(float val, float a, float b) {
	if (val < a)
		val = a;
	if (val > b)
		val = b;
	return val;
}

float magnitude(sf::Vector2i u) {
	return sqrt(u.x * u.x + u.y * u.y);
}

void Dijkstra::compute(const sf::Vector2i& start) {
	g.clear();
	int maxCellW = Game::W / Entity::stride + 1;
	int maxCellH = Game::H / Entity::stride + 1;
	for (int y = 0; y < maxCellH; ++y) {
		for (int x = 0; x < maxCellW; ++x) {
			if (!Game::isColliding(x, y))
				g[sf::Vector2i(x, y)] = true;
		}
	}
	init(start);
	while (!queue.empty()) {
		std::optional<sf::Vector2i> s1 = findMin(queue);
		if (s1 == std::nullopt) break;

		auto pos = std::find(queue.begin(), queue.end(), *s1);
		queue.erase(pos);

		sf::Vector2i dirs[] = {
			sf::Vector2i(0, 1),
			sf::Vector2i(0, -1),
			sf::Vector2i(1, 0),
			sf::Vector2i(-1, 0)
		};
		for (int i = 0; i < 4; i++) {
			sf::Vector2i neighbor = *s1 + dirs[i];
			maj_distances(*s1, neighbor);
		}
	}
}

void Dijkstra::init(const sf::Vector2i& start) {
	for (auto d : g) {
		dist[d.first] = FLT_MAX;
		queue.push_back(d.first);
	}
	dist[start] = 0;
}

std::optional<sf::Vector2i> Dijkstra::findMin(std::vector<sf::Vector2i>& q) {
	float min = FLT_MAX;
	std::optional<sf::Vector2i> sommet = std::nullopt;
	for (auto& s : q) {
		if (dist[s] < min) {
			min = dist[s];
			sommet = s;
		}
	}
	return sommet;
}
