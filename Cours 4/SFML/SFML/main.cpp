#include <SFML/Graphics.hpp>
#include <math.h>
#include "Curve.h"
#include "Boulette.h"


int main()
{
    #pragma region Shapes
    sf::Color orange(255, 128, 0);
    sf::RenderWindow window(sf::VideoMode(900, 720), "SFML works!");
    sf::CircleShape circle(10);
    circle.setOrigin(10, 10);
    circle.setFillColor(sf::Color::Yellow);
    
    sf::RectangleShape rectangle(sf::Vector2f(80, 5));
    rectangle.setFillColor(sf::Color(25, 25, 25));
    rectangle.setOutlineColor(orange);
    rectangle.setOutlineThickness(4);
    rectangle.setPosition(450, 360);
    rectangle.setOrigin(4, 0);
    #pragma endregion

    sf::Font font;
    if (!font.loadFromFile("res/NotoSerif-Regular.ttf"))
    {
        throw "no font";
    }

    sf::VertexArray mountain(sf::LinesStrip);
    sf::Color col = sf::Color::Cyan;

    Bullet bullet;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            #pragma region moveRectangle
            sf::Vector2f pos = rectangle.getPosition();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                pos.x += 10;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                pos.x -= 10;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                pos.y += 10;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                pos.y -= 10;
            }
            rectangle.setPosition(pos);
            #pragma endregion

            #pragma region aim
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            circle.setPosition(sf::Vector2f(mousePos));
            sf::Vector2f characterToMouse(
                mousePos.x - rectangle.getPosition().x,
                mousePos.y - rectangle.getPosition().y);

            float rad2deg = 57.2958f;
            float angleC2M = atan2(characterToMouse.y, characterToMouse.x);
            rectangle.setRotation(angleC2M * rad2deg);
            #pragma endregion

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                std::vector<float> pos = { rectangle.getPosition().x, rectangle.getPosition().y };
                std::vector<float> dir = { sf::Mouse::getPosition().x - rectangle.getPosition().x, sf::Mouse::getPosition().y - rectangle.getPosition().y };
                bullet.create(BulletShape(), pos, dir);
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                /*if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2f mountainVec = mountain[mountain.getVertexCount()].position;
                    sf::Vector2f clic = (sf::Vector2f)sf::Mouse::getPosition(window);
                    for (int i = mountainVec.x; clic.x; i++) {
                        float t = 1.0f * i * mountain[mountain.getVertexCount()].position.x;
                        float x = catmull(mountainVec.x, mountainVec.x, clic.x, clic.x, t);
                        float y = catmull(mountainVec.y, mountainVec.y, clic.y, clic.y, t);
                        mountain.append(sf::Vertex(sf::Vector2f(x, y), col));
                    }

                }*/
                mountain.append(sf::Vertex((sf::Vector2f)sf::Mouse::getPosition(window), col));
            }

        }

        window.clear(sf::Color::Black);
        drawGround(window);
        drawMountain(window);
        window.draw(circle);
        window.draw(mountain);
        window.draw(rectangle);
        window.display();
    }

    return 0;
}

