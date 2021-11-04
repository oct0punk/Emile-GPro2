#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(50);
    shape.setFillColor(sf::Color::Yellow);



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                shape.setOrigin(shape.getOrigin().x - 1, 0);
        }

        window.clear(sf::Color::Blue);
        window.draw(shape);
        window.display();
    }

    return 0;
}