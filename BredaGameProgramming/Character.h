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
// Protected to be used later in the child classes
protected:
    float time;
    sf::Vector2f target;
    sf::Sprite character = sf::Sprite(texture);
    bool attacking;
public:
    
    Character(const std::string& texturePath, float xCoordinate, float yCoordinate, const std::string& battleSide, const std::string& soundPath, const std::string& characterName, float healthLimit, float characterAttackRange, float attackDamage, float characterVelocity, float targetRange);
    
    // Coordinates the movement and attack logic for the character
    void move_and_attack(std::vector<std::unique_ptr<Character>>& enemies, float& deltaTime);

    // Moves the character towards the target
    void move_character(float xDistance, float yDistance, float& time, sf::Vector2f& currentPos);
    
    // Returns character's current position
    sf::Vector2f get_position();
    
    // Decreases the character's hp by the damage dealt to it
    void take_damage(float damageTaken);

    // Deletes the enemy character
    void delete_target(Character *targetCharacter, std::vector<std::unique_ptr<Character>>& enemies);

    // Displays the character
    virtual void draw_character(sf::RenderWindow& window);
    
    // Identifies the closest enemy character and returns its index
    int identify_closest_target(std::vector<std::unique_ptr<Character>>& enemies);

    // Returns the characters name (type)
    std::string get_name();

    // Displays and manages the health bar of the character
    void display_health_bar(sf::RenderWindow& window);
    
    // Returns the character's current hp
    float get_hp();

};

// Goblin
class Goblin : public Character {
public: 
    Goblin(float xCoordinate, float yCoordinate, const std::string battleSide) : Character("images/Goblin.png", xCoordinate, yCoordinate, battleSide, "sounds/goblin.mp3", "Goblin", 70, 50, 20, 50, 100) {}
    
};

// Giant
class Giant : public Character {
public:
    Giant(float xCoordinate, float yCoordinate, const std::string battleSide) : Character("images/Giant.png", xCoordinate, yCoordinate, battleSide, "sounds/giant.mp3", "Giant", 200, 10, 70, 25, 100) {}

};

// Tower
class Tower : public Character {
public:
    Tower(float xCoordinate, float yCoordinate, const std::string battleSide) : Character("images/Tower.png", xCoordinate, yCoordinate, battleSide, "", "Tower", 250, 50, 1, 0, 1) {}
};

// Archer
class Archer : public Character {
private:
    Arrow arrow;
public:
    
    Archer(float xCoordinate, float yCoordinate, const std::string battleSide) : Character("images/Archer.png", xCoordinate, yCoordinate, battleSide, "sounds/archer.mp3", "Archer", 20, 200, 10, 30, 300) {}
    virtual void draw_character(sf::RenderWindow& window) override;
};