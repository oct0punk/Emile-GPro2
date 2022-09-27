#include "World.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

void World::update(double dt) {
	for (auto e : data) {
		if (e->CollisionWithWorld(vecs))
			e->simulated = false;
		else
			e->simulated = true;
		e->update(dt);
	}
	float arrSize = *gridSize * *gridSize;
	if (arrSize != arr.getVertexCount()) {
		arr.clear();
		for (int x = 1; x < 1240 / *gridSize; x++) {
			for (int y = 1; y < 720 / *gridSize; y++) {
				arr.append(sf::Vertex(sf::Vector2f(x * *gridSize, y * *gridSize)));
			}
		}
	}
}


void World::draw(sf::RenderWindow& window) {
	window.clear();
	for (auto e : data) {
		e->draw(window);
	}
	sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(*gridSize, *gridSize));
	for (auto v : vecs) {
		sf::RectangleShape rect(*shape);
		rect.setPosition(v.x * *gridSize, v.y * *gridSize);
		window.draw(rect);
	}
	window.draw(arr);
}

void World::AppendBlock(sf::Vector2i pos) {
	pos.x /= *gridSize;
	pos.y /= *gridSize;
	for (auto v : vecs)
		if (v == sf::Vector2f(pos.x, pos.y))
			return;
	vecs.push_back(sf::Vector2f(pos.x, pos.y));
}

Audio::Audio() {
}
