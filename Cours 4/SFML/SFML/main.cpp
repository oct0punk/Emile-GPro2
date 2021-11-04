#include <SFML/Graphics.hpp>
#include <math.h>

int main()
{
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

    sf::Font font;
    if (!font.loadFromFile("res/NotoSerif-Regular.ttf"))
    {
        throw "no font";
    }


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

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {

            }

        }
        window.clear(sf::Color::Black);
        window.draw(circle);
        window.draw(rectangle);
        window.display();
    }

    return 0;
}