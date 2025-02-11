#pragma once
#include <SFML/Graphics.hpp>
class Circle {
public:
    float radius = 7.0;
    sf::CircleShape circle;
    Circle() {

    }
    Circle(float circleX, float circleY) {
        circle.setRadius(radius);
        circle.setOrigin(circle.getGeometricCenter());
        circle.setFillColor(sf::Color::Cyan);
        circle.setPosition({ circleX, circleY });
    }

    void go_up();
    void go_down();
    void go_right();
    void go_left();

    void draw_circle(sf::RenderWindow& window);
};
class Character {
public:
    enum directions;
    sf::Texture texture;
    sf::Sprite character;


    void 
    

    void draw_character(sf::RenderWindow& window);
};