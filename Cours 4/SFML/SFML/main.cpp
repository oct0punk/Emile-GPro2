#include <SFML/Graphics.hpp>
#include <math.h>

void drawMountain(sf::RenderWindow& window) {
    sf::VertexArray arr;
    arr.setPrimitiveType(sf::LinesStrip);
    sf::Color col = sf::Color::Red;

    float baseLine = 660;

    for (int i = 0; i < window.getSize().x / 2; i++) {
        arr.append(sf::Vertex(sf::Vector2f(i, baseLine - (i * i) / 1000), col));
    }
    for (int i = window.getSize().x / 2 + 1; i < window.getSize().x; i++) {
        arr.append(sf::Vertex(sf::Vector2f(i, baseLine), col));
    }

    window.draw(arr);
}

void drawGround(sf::RenderWindow& window) {
    sf::VertexArray arr;
    arr.setPrimitiveType(sf::LinesStrip);
    sf::Color col = sf::Color::Yellow;

    float baseLine = 660;
    sf::Vector2f a(0, baseLine);
    sf::Vector2f b(window.getSize().x, baseLine);

    arr.append(sf::Vertex(a, col));
    arr.append(sf::Vertex(b, col));
    window.draw(arr);
}


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
    rectangle.setPosition(450, 660);
    rectangle.setOrigin(4, 0);

    sf::Font font;
    if (!font.loadFromFile("res/NotoSerif-Regular.ttf"))
    {
        throw "no font";
    }

    sf::VertexArray mountain(sf::LinesStrip);
    sf::Color col = sf::Color::Cyan;
    

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