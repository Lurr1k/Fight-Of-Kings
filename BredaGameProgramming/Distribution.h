#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Potion.h"

class Distribution {
private:

	sf::FloatRect enemySide;
	float yLimit;
	float xLimit;
	float timer;
	Potion enemyLevel;

	float randomTime;

public:
	
	Distribution();

	// Generates the spawn location for the enemy characters
	sf::Vector2f generate_spawn_location(std::vector<std::unique_ptr<Character>>& heroes);

	// Spawns the enemies on the enemy side
	void spawn_enemies(float& deltaTime, std::vector<std::unique_ptr<Character>>& heroes, std::vector<std::unique_ptr<Character>>& enemies);

	// Checks whether the timer allows to spawn enemies and regenerates the pseudorandom time pause
	bool timing_correct(float
		
		
		
		deltaTime);
	
	// Chooses the type of the enemy to spawn
	std::string choose_type();

	// Resets the potion level for the enemy
	void reset_potion();
};