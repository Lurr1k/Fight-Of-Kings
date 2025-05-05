#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

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

public:
    sf::Sprite character = sf::Sprite(texture);
    Character(const std::string& TEXTUREPATH, float xCoordinate, float yCoordinate, const std::string& battleSide, const std::string& soundPath, const std::string& characterName, float healthLimit, float characterAttackRange, float attackDamage, float attackCoolDown, float characterVelocity, float targetRange);
    
    
    void move_towards_enemy(std::vector<std::unique_ptr<Character>> &enemies, float &deltaTime);

    void move_character(float xDistance, float yDistance, float &time, sf::Vector2f &currentPosition);

    void set_position(float x, float y);

    sf::Vector2f get_position();
    
    void take_damage(float damageTaken, float &deltaTime);

    void delete_target(Character *target, std::vector<std::unique_ptr<Character>> &enemies);

    void draw_character(sf::RenderWindow& window);
    
    float get_velocity();
    
    int identify_closest_target(std::vector<std::unique_ptr<Character>> &enemies);

    std::string get_name();

    void display_health_bar(sf::RenderWindow& window);
    
    float get_hp();
};

class Goblin : public Character {
public: 
    Goblin(float xCoordinate, float yCoordinate, const std::string battleSide) : Character("images/Goblin.png", xCoordinate, yCoordinate, battleSide, "sounds/goblin.mp3", "Goblin", 50, 50, 25, 1, 50, 100) {}
    
};

class Giant : public Character {
public:
    Giant(float xCoordinate, float yCoordinate, const std::string battleSide) : Character("images/Giant.png", xCoordinate, yCoordinate, battleSide, "sounds/giant.mp3", "Giant", 125, 10, 70, 3, 10, 100) {}

};

class Tower : public Character {
public:
    Tower(float xCoordinate, float yCoordinate, const std::string battleSide) : Character("images/Tower.png", xCoordinate, yCoordinate, battleSide, "", "Tower", 125, 50, 1, 1, 0, 1) {}
};

class Archer : public Character {
public:
    Archer(float xCoordinate, float yCoordinate, const std::string battleSide) : Character("images/Archer.png", xCoordinate, yCoordinate, battleSide, "sounds/archer.mp3", "Archer", 20, 200, 30, 1, 50, 300) {}

};