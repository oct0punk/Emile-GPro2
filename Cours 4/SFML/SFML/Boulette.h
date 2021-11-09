#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/CircleShape.hpp"

class Bullet {
public :
    sf::CircleShape b;

    std::vector<float> px;
    std::vector<float> py;

    std::vector<float> dx;
    std::vector<float> dy;

    std::vector<bool> alive;

    void create(sf::CircleShape shape, std::vector<float> pos, std::vector<float> dir) {
        b = shape;
        alive = std::vector<bool>(false);        
        px.resize(1);
        py.resize(1);
        dx.resize(1);
        dy.resize(1);

        px[0] = pos[0];
        py[0] = pos[1];

        dx[0] = dir[0];
        dy[0] = dir[1];
    }

    void update(double dt) {
        for (int i = 0; i < px.size(); i++) {
            if (alive[i]) {
                px[i] += dx[i] * dt;
                py[i] += dy[i] * dt;
                if ((px[i] > 3000) || (px[i] < -100) ||
                    (py[i] > 3000) || (py[i] < -100)) {
                    alive[i] = false;
                }
            }
        }
    }

    void Draw(sf::RenderWindow& win) {
        int idx = 0;
        const int sz = px.size();
        while (idx < sz) {
            if (alive[sz]) {

            }
        }
        win.draw(b);
    }
};

sf::CircleShape BulletShape() {
    sf::CircleShape circle(15);
    circle.setOrigin(15, 15);
    circle.setFillColor(sf::Color::Yellow);
    circle.setOutlineColor(sf::Color::Red);
    circle.setOutlineThickness(5);
    return circle;
}

sf::Vector2f BulletDirection(sf::CircleShape boulettes, sf::RenderWindow& window) {
    sf::Vector2f direction = sf::Vector2f(
        (sf::Mouse::getPosition(window).x - boulettes.getPosition().x),
        (sf::Mouse::getPosition(window).y - boulettes.getPosition().y));

    float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);
    return direction / (magnitude * 5);
}

