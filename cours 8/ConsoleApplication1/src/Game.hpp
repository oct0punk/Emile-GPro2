#pragma once
#include "Particle.hpp"
#include "Entity.hpp"
#include <unordered_map>

float clamp(float val, float a, float b);

namespace std {
	template <>
	struct hash<sf::Vector2i> {
		std::size_t operator()(const sf::Vector2i& k) const {
			using std::size_t;
			using std::hash;
			using std::string;
			return k.x | (k.y << 12);
		}
	};
}

class Dijkstra {
public:
	std::unordered_map<sf::Vector2i, float> dist;
};


class Game {
public:
	static inline const int W = 1280;
	static inline const int H = 720;
	static int			shake;
	static Particle		parts;

	static std::vector<sf::Vector2i> walls;

	static Entity*		player;
	static void			particlesAt(sf::Vector2f pos);
	static void			init();
	static void			im();
	static void			update(double dt);
	static void			render(sf::RenderWindow &win);
};