#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Character.h"
#include "Potion.h"

// Spawn on the same side as the character. If there is more than one - one with more characters. 
//Generate based on times and current elixir levels
//If no active enemies exist, spawn a character to attack the towers

class Distribution {
private:
	float deltaTime;
	sf::FloatRect enemySide;
	float yLimit;
	float xLimit;
	float timer;
	Potion enemyLevel;
public:

	Distribution();


	sf::Vector2f generate_spawn_location(std::vector<std::unique_ptr<Character>>& heroes);

	void spawn_enemies(float& deltaTime, std::vector<std::unique_ptr<Character>>& heroes, std::vector<std::unique_ptr<Character>>& enemies);

	bool timing_correct(float &deltaTime);
	
	std::string choose_type();
};