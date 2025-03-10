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

sf::Vector2f Circle::get_position() {

    return (circle.getPosition());
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

void Character::move_towards_enemy(Circle& enemy, std::vector<Circle>& enemies) {
    std::string moving = "";
    sf::Vector2f target = enemy.get_position();
    sf::Vector2f currentPosition = character.getPosition();

    if (target.x < currentPosition.x) {
        moving = "left";
        character.move({ -1,0 });
        character.setRotation(sf::degrees(-90));
    }
    else if (target.x > currentPosition.x) {
        moving = "right";
        character.move({ 1,0 });
        character.setRotation(sf::degrees(90));
    }

    if (target.y < currentPosition.y) {
        character.move({ 0, -1 });
        if (moving == "left") {
            character.setRotation(sf::degrees(-45));
        }
        else if (moving == "right") {
            character.setRotation(sf::degrees(45));
        }
        else {
            character.setRotation(sf::degrees(0));
        }
    }

    else if (target.y > currentPosition.y) {
        character.move({ 0,1 });
        if (moving == "left") {
            character.setRotation(sf::degrees(-135));
        }
        else if (moving == "right") {
            character.setRotation(sf::degrees(135));
        }
        else {
            character.setRotation(sf::degrees(180));
        }
    }
    if ( target == currentPosition) {
        delete_target(&enemy, enemies);
    }
}

void Character::take_damage() {
    if (hp > 0) {
        hp -= 1;
    }
    
}

void Character::delete_target(Circle* target, std::vector<Circle>& enemies) {
    for (std::size_t i = 0; i < enemies.size(); i++) {
        if (&enemies[i] == target) {
            enemies.erase(enemies.begin()+i);

            break;
        }
    }
    
}

void Character::draw_character(sf::RenderWindow& window) {
    window.draw(character);
}