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
    maxHp = healthLimit;
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
    sf::Vector2f bounds = character.getLocalBounds().size;
    character.setOrigin({ bounds.x / 2, bounds.y / 2 });
}

void Character::set_position(float x, float y) {
    character.setPosition({ x,y });
}

void Character::move_towards_enemy(std::vector<std::unique_ptr<Character>> &enemies, float &deltaTime) {
    if (name != "Tower") {
        std::string moving = "";
        bool attacking = false;
        float time = deltaTime;
        int targetIndex = identify_closest_target(enemies);
        sf::Vector2f target = enemies[targetIndex]->get_position();
        sf::Vector2f currentPosition = character.getPosition();
        float xDistance = target.x - currentPosition.x;
        float yDistance = target.y - currentPosition.y;
        float distance = (std::sqrt(xDistance * xDistance + yDistance * yDistance));
        if (distance < attackRange) {
            if (enemies[targetIndex]->get_hp() > 0) {
                enemies[targetIndex]->take_damage(damage, deltaTime);
                attacking = true;
            }
            else {
                delete_target(enemies[targetIndex].get(), enemies);
            }
        }
        if (xDistance < -2 and not attacking) {
            moving = "left";
            character.move({ -velocity * time, 0.f });
            character.setRotation(sf::degrees(-90));
        }
        else if (xDistance > 2 and not attacking) {
            moving = "right";
            character.move({ velocity * time, 0.f });
            character.setRotation(sf::degrees(90));
        }

        if (yDistance < -2 and not attacking) {
            character.move({ 0, -velocity * time });
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

        else if (yDistance > 2 and not attacking) {
            character.move({ 0.f, velocity * time });
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

void Character::take_damage(float damageTaken, float &deltaTime) {
    hp -= damageTaken*deltaTime;
}

float Character::get_velocity() {

    return velocity;
}

std::string Character::get_name() {

    return name;
}

int Character::identify_closest_target(std::vector<std::unique_ptr<Character>>& enemies) {
    sf::Vector2f positionDifference;
    float newDistance;
    int chosenIndex = 0;
    float distance = 1000;
    for (int i = 0; i < enemies.size(); i++) {
        positionDifference = character.getPosition() - enemies[i]->get_position();
        newDistance = std::sqrt((positionDifference.x * positionDifference.x) + (positionDifference.y * positionDifference.y));
        if (newDistance < distance) {
            distance = newDistance;
            chosenIndex = i;
        }
    }
    return chosenIndex;
}

void Character::display_health_bar(sf::RenderWindow &window) {
    sf::RectangleShape barBackground;
    sf::RectangleShape healthBar;
    sf::Vector2f characterToBarDistance = { 0, 30 };
    sf::Vector2f healthBarPosition = character.getPosition() + characterToBarDistance;
    barBackground.setSize({ 40, 4 });
    barBackground.setOrigin({20, 0});
    barBackground.setPosition(healthBarPosition);
    barBackground.setFillColor(sf::Color::Green);

    healthBar.setSize({ 30 * (hp/maxHp), 2});
    healthBar.setOrigin({0,0});
    healthBar.setPosition(healthBarPosition + sf::Vector2f({-15, 1}));
    healthBar.setFillColor(sf::Color::Red);

    window.draw(barBackground);
    window.draw(healthBar);
    

}

float Character::get_hp() {

    return hp;
}