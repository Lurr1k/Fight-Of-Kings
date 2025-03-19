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
    sf::Vector2f get_position();

    void draw_circle(sf::RenderWindow& window);
};

class Character {
private:
    sf::Texture texture;
    std::unordered_map<int, std::string> characters;
    float hp;
    float attackRange;
    std::string name;


public:
    sf::Sprite character;
    Character(const std::string& TEXTUREPATH, std::string characterName, float healthLimit, float range);
    
    
    void move_towards_enemy(Circle& enemy, std::vector<Circle>& enemies);

    void set_position(float x, float y);
    
    void take_damage();

    void delete_target(Circle* target, std::vector<Circle>& enemies);

    void draw_character(sf::RenderWindow& window);
    
    void character_setup(float healthLimit, float range);
};

class Goblin : public Character {
public: 
    Goblin(const std::string& TEXTUREPATH) : Character(TEXTUREPATH, "Goblin", 500, 200) {}

};