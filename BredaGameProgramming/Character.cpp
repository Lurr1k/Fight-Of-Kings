#include "Character.h"
#include "SFML/Graphics.hpp"
#include <iostream>
sf::CircleShape circle;

void Circle::go_up() {
    circle.move({ 0, -1 });
}

void Circle::go_down() {
    circle.move({ 0,10 });
}
void Circle::go_right() {
    circle.move({ 10,0 });
}
void Circle::go_left() {
    circle.move({ -10,0 });
}
void Circle::draw_circle(sf::RenderWindow& window) {
    window.draw(circle);
}

Character::Character(const std::string& TEXTUREPATH) : texture(), character(texture) {
    if (!texture.loadFromFile(TEXTUREPATH)) {

    }
    else {
        std::cout << "Shmobus";
        character.setTexture(texture, true);
    }
    
}

void Character::set_position(float x, float y) {
    character.setPosition({ x,y });
}

void Character::move_towards_enemy(Circle& shmobus) {
    sf::Vector2 target = shmobus.getPosition();
    std::cout << target.x << target.y;
    sf::Vector2 currentPosition = character.getPosition();
    if (target.x > currentPosition.x) {
        std::cout << "x+";
        character.move({ -1,0 });
    }
    else if (target.x < currentPosition.x) {

        character.move({ 1,0 });
    }
    if (target.y > currentPosition.y) {
        std::cout << "y+";
        character.move({ 0, -1 });
    }
    else if (target.y < currentPosition.y) {
        character.move({ 0,1 });

    }
    if (target == currentPosition) {
        std::cout << "Yay";
    }
}

void Character::draw_character(sf::RenderWindow& window) {
    window.draw(character);
}