#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Arrow.h"

class Character {
private:
    sf::Texture texture;
    float maxHp;
    float hp;
    float attackRange;
    std::string name;
    float damage;
    float coolDown;
    float velocity;
    float sightRange;
    std::string heroOrEnemy;
    sf::RectangleShape barBackground;
    sf::RectangleShape healthBar;
    sf::SoundBuffer soundBuffer;
    sf::Sound characterSound = sf::Sound(soundBuffer);
protected:
    float time;
    sf::Vector2f target;
    sf::Sprite character = sf::Sprite(texture);
    bool attacking;
public:
    
    Character(const std::string& texturePath, float xCoordinate, float yCoordinate, const std::string& battleSide, const std::string& soundPath, const std::string& characterName, float healthLimit, float characterAttackRange, float attackDamage, float characterVelocity, float targetRange);
    
    
    void move_and_attack(std::vector<std::unique_ptr<Character>>& enemies, float& deltaTime);

    void move_character(float xDistance, float yDistance, float& time, sf::Vector2f& currentPos);

    void set_position(float x, float y);

    sf::Vector2f get_position();
    
    void take_damage(float damageTaken);

    void delete_target(Character *targetCharacter, std::vector<std::unique_ptr<Character>>& enemies);

    virtual void draw_character(sf::RenderWindow& window);
    
    float get_velocity();
    
    int identify_closest_target(std::vector<std::unique_ptr<Character>>& enemies);

    std::string get_name();

    void display_health_bar(sf::RenderWindow& window);
    
    float get_hp();

};

class Goblin : public Character {
public: 
    Goblin(float xCoordinate, float yCoordinate, const std::string battleSide) : Character("images/Goblin.png", xCoordinate, yCoordinate, battleSide, "sounds/goblin.mp3", "Goblin", 50, 50, 25, 50, 100) {}
    
};

class Giant : public Character {
public:
    Giant(float xCoordinate, float yCoordinate, const std::string battleSide) : Character("images/Giant.png", xCoordinate, yCoordinate, battleSide, "sounds/giant.mp3", "Giant", 200, 10, 70, 25, 100) {}

};

class Tower : public Character {
public:
    Tower(float xCoordinate, float yCoordinate, const std::string battleSide) : Character("images/Tower.png", xCoordinate, yCoordinate, battleSide, "", "Tower", 250, 50, 1, 0, 1) {}
};

class Archer : public Character {
private:
    Arrow arrow;
public:
    
    Archer(float xCoordinate, float yCoordinate, const std::string battleSide) : Character("images/Archer.png", xCoordinate, yCoordinate, battleSide, "sounds/archer.mp3", "Archer", 20, 200, 15, 40, 300) {}
    virtual void draw_character(sf::RenderWindow& window) override;
};