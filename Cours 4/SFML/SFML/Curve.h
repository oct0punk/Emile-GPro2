#pragma once

static float catmull(float p0, float p1, float p2, float p3, float t) {
	float q = 2.0f * p1;
	float t2 = t * t;

	q += (-p0 + p2) * t;
	q += (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * t2;
	q += (-p0 + 3 * p1 - 3 * p2 + p3) * t2 * t;

	return 0.5f * q;
}

void drawMountain(sf::RenderWindow& window) {
    sf::VertexArray arr;
    arr.setPrimitiveType(sf::LinesStrip);
    sf::Color col = sf::Color::Red;

    float baseLine = 660;
    sf::Vector2f a(0, baseLine);
    sf::Vector2f b(window.getSize().x / 2, baseLine - window.getSize().y / 2);
    sf::Vector2f c(window.getSize().x, baseLine);
    arr.append(sf::Vertex(a, sf::Color::Red));
    arr.append(sf::Vertex(b, sf::Color::Green));
    arr.append(sf::Vertex(c, sf::Color::Blue));
    for (int i = 0; i < 256; ++i) {
        float t = 1.0f * i / 256;
        float x = (window.getSize().x - 0) * t;
        float y = catmull(a.y, a.y, b.y, c.y, t);
        arr.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::Yellow));
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
