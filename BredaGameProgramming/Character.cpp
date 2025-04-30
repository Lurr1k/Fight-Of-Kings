#include "Character.h"
#include "SFML/Graphics.hpp"
#include <iostream>

Character::Character(const std::string& TEXTUREPATH, float xCoordinate, float yCoordinate, std::string battleSide, std::string soundPath, std::string characterName, float healthLimit, float characterAttackRange, float attackDamage, float attackCoolDown, float characterVelocity, float targetRange) {
    
    hp = healthLimit;
    maxHp = healthLimit;
    attackRange = characterAttackRange;
    name = characterName;
    damage = attackDamage;
    coolDown = attackCoolDown;
    velocity = characterVelocity;
    sightRange = targetRange;
    heroOrEnemy = battleSide;
    
    texture.loadFromFile(TEXTUREPATH);
    character.setTexture(texture, true);

    if (name != "Tower") {
        std::cout << soundPath;
        soundBuffer.loadFromFile(soundPath);
        characterSound.setBuffer(soundBuffer);
        characterSound.setVolume(40);
        characterSound.play();
    }

    barBackground.setSize({ 40, 4 });
    barBackground.setOrigin({ 20, 0 });
    barBackground.setFillColor(sf::Color::Green);

    character.setPosition({xCoordinate, yCoordinate});
    sf::Vector2f bounds = character.getLocalBounds().size;
    character.setOrigin({ bounds.x / 2, bounds.y / 2 });
}

void Character::set_position(float x, float y) {
    character.setPosition({ x,y });
}

void Character::move_towards_enemy(std::vector<std::unique_ptr<Character>> &enemies, float &deltaTime) {
    if (name != "Tower") {
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
            }
            else {
                delete_target(enemies[targetIndex].get(), enemies);
            }
        }
        else if ((currentPosition.y >= 450) and (currentPosition.y <= 510) and not ((currentPosition.x >= 50 and currentPosition.x <= 154) or (currentPosition.x >= 595 and currentPosition.x <= 700))) {
            if (currentPosition.y < 480) {
                character.setPosition({ currentPosition.x, 450 });
            }
            else {
                character.setPosition({ currentPosition.x, 510 });
            }

            if (currentPosition.x < 375) {
                character.move({ -velocity * time, 0.f });
                character.setRotation(sf::degrees(-90));
            }
            else {
                character.move({ velocity * time, 0.f });
                character.setRotation(sf::degrees(90));
            }
        }
        else {
            move_character(xDistance, yDistance, time, currentPosition);
        }
        
    }
}

void Character::move_character(float xDistance, float yDistance, float &time, sf::Vector2f &currentPosition) {
    std::string moving = "";
    if (xDistance < -2 and not (currentPosition.y >= 450 and currentPosition.y <= 510)) {
        moving = "left";
        character.move({ -velocity * time, 0.f });
        character.setRotation(sf::degrees(-90));
    }
    else if (xDistance > 2 and not (currentPosition.y >= 450 and currentPosition.y <= 510)) {
        moving = "right";
        character.move({ velocity * time, 0.f });
        character.setRotation(sf::degrees(90));
    }

    if (yDistance < -2) {
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

    else if (yDistance > 2) {
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
    int chosenIndex = -1;
    float distance = 1000;
    for (int i = 0; i < enemies.size(); i++) {
        positionDifference = character.getPosition() - enemies[i]->get_position();
        newDistance = std::sqrt((positionDifference.x * positionDifference.x) + (positionDifference.y * positionDifference.y));
        if (newDistance < distance and newDistance < sightRange) {
            distance = newDistance;
            chosenIndex = i;
        }
    }
    if (chosenIndex == -1) {
        distance = 1000;
        for (int i = 0; i < enemies.size(); i++) {
            positionDifference = character.getPosition() - enemies[i]->get_position();
            newDistance = std::sqrt((positionDifference.x * positionDifference.x) + (positionDifference.y * positionDifference.y));
            if (newDistance < distance and (enemies[i]->get_name() == "Tower")) {
                distance = newDistance;
                chosenIndex = i;
            }
        }
    }
    if (chosenIndex == -1) {
        chosenIndex = 0;
    }
    return chosenIndex;
}

void Character::display_health_bar(sf::RenderWindow &window) {
    sf::Vector2f characterToBarDistance;
    if (hp < 0) {
        hp = 0;
    }
    if (heroOrEnemy == "enemy") {
        characterToBarDistance = { 0, -30 };
        barBackground.setFillColor(sf::Color::Red);
        healthBar.setFillColor(sf::Color::Green);
    }
    else {
        characterToBarDistance = { 0, 30 };
        barBackground.setFillColor(sf::Color::Green);
        healthBar.setFillColor(sf::Color::Red);
    }

    sf::Vector2f healthBarPosition = character.getPosition() + characterToBarDistance;
    barBackground.setPosition(healthBarPosition);
    healthBar.setSize({ 30 * (hp/maxHp), 2});
    healthBar.setOrigin({0,0});
    healthBar.setPosition(healthBarPosition + sf::Vector2f({-15, 1}));

    window.draw(barBackground);
    window.draw(healthBar);
    

}

float Character::get_hp() {

    return hp;
}








