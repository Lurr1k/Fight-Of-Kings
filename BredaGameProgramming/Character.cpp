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

Character::Character(const std::string& TEXTUREPATH, float xCoordinate, float yCoordinate, std::string characterName, float healthLimit, float range, float attackDamage, float attackCoolDown, float characterVelocity) : texture(), character(texture) {
    
    hp = healthLimit;
    attackRange = range;
    name = characterName;
    damage = attackDamage;
    coolDown = attackCoolDown;
    velocity = characterVelocity;
    
    if (!texture.loadFromFile(TEXTUREPATH)) {

    }
    else {
        character.setTexture(texture, true);
    }

    character.setPosition({xCoordinate, yCoordinate});
}

void Character::set_position(float x, float y) {
    character.setPosition({ x,y });
}

void Character::move_towards_enemy(Character& enemy, std::vector<std::unique_ptr<Character>> &enemies) {
    std::string moving = "";
    sf::Vector2f target = enemy.get_position();
    sf::Vector2f currentPosition = character.getPosition();
    float xDistance = target.x - currentPosition.x;
    float yDistance = target.y - currentPosition.y;
    float distance = (std::sqrt(xDistance*xDistance + yDistance*yDistance));
    if (xDistance < 0) {
        moving = "left";
        character.move({ -velocity,0 });
        character.setRotation(sf::degrees(-90));
    }
    else if (xDistance > 0) {
        moving = "right";
        character.move({ velocity,0 });
        character.setRotation(sf::degrees(90));
    }

    if (yDistance < 0) {
        character.move({ 0, -velocity });
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

    else if (yDistance > 0) {
        character.move({ 0, velocity });
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
    if ( distance < 5) {
        delete_target(&enemy, enemies);
    }
}

void Character::delete_target(Character *target, std::vector<std::unique_ptr<Character>> &enemies) {
    for (std::size_t i = 0; i < enemies.size(); i++) {
        if (enemies[i].get() == target) {
            enemies.erase(enemies.begin()+i);

            break;
        }
    }
    
}
sf::Vector2f Character::get_position() {
    return character.getPosition();
}

void Character::draw_character(sf::RenderWindow& window) {
    window.draw(character);
}

void Character::take_damage(float damageTaken) {
    hp -= damageTaken;
    std::cout << hp;
}

float Character::get_velocity() {

    return velocity;
}

std::string Character::get_name() {

    return name;
}