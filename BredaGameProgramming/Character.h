#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
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
private:
    sf::Texture texture;
    sf::Sprite character;
public:
    Character(const std::string& TEXTUREPATH);



    void set_position(float x, float y);

    void draw_character(sf::RenderWindow& window);
}