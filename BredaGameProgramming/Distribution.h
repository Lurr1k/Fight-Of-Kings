#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Character.h"
#include "Potion.h"

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