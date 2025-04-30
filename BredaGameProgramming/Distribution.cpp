#include <iostream>
#include "SFML/Graphics.hpp"
#include "Distribution.h"
#include "Character.h"
#include "Potion.h"


Distribution::Distribution() {
	xLimit = 750;
	yLimit = 450;
	enemySide = sf::FloatRect({ 0,0 }, { xLimit, yLimit });
}

sf::Vector2f Distribution::generate_spawn_location(std::vector<std::unique_ptr<Character>>& heroes) {
	float generatedX;
	float generatedY;
	sf::Vector2f generatedPos;
	int characterCount = 0;
	int rightCount = 0;
	int leftCount = 0;
	for (int i = 0; i < heroes.size(); i++) {
		if (heroes[i]->get_name() != "Tower") {
			characterCount += 1;
			if ((heroes[i]->get_position()).x > 375) {
				rightCount += 1;
			}
			else {
				leftCount += 1;
			}
		}
	}


	if (characterCount == 0) {
		generatedX = rand() % 750;
	}
	else if (rightCount > leftCount) {
		generatedX = (rand() % 375)+(375);
	}
	else {
		generatedX = rand() % (375);
	}

	generatedY = rand() % 450;
	generatedPos = { generatedX, generatedY };
	
	return generatedPos;
}

bool Distribution::timing_correct(float &deltaTime) {
	timer += deltaTime;
	bool timing = false;
	if (timer >= 5) {
		timer = 0;
		timing = true;
	}
	else {
		timing = false;
	}
	return timing;
}

std::string Distribution::choose_type() {
	std::string chosenType;
	float potionLevel = enemyLevel.get_potion_level();
	if (potionLevel < 3 and potionLevel >= 2) {
		chosenType = "goblin";
		enemyLevel.decrease_potion_level(2);
	}
	else if (potionLevel < 5 and potionLevel >= 3) {
		chosenType = "archer";
		enemyLevel.decrease_potion_level(3);
	}
	else if (potionLevel < 10 and potionLevel >= 5) {
		chosenType = "giant";
		enemyLevel.decrease_potion_level(5);
	}

	return chosenType;
}

void Distribution::spawn_enemies(float &deltaTime, std::vector<std::unique_ptr<Character>>& heroes, std::vector<std::unique_ptr<Character>>& enemies) {
	// wait for timing 
	// choose enemy type
	// generate position
	// spawn the character
	enemyLevel.increase_potion_level(deltaTime);
	std::string chosenType;
	sf::Vector2f spawnPosition;
	if (timing_correct(deltaTime)) {
		chosenType = choose_type();
		spawnPosition = generate_spawn_location(heroes);
		if (chosenType == "goblin") {
			enemies.emplace_back(std::make_unique<Goblin>(spawnPosition.x, spawnPosition.y, "enemy"));
		}
		else if (chosenType == "giant") {
			enemies.emplace_back(std::make_unique<Giant>(spawnPosition.x, spawnPosition.y, "enemy"));
		}
		else if (chosenType == "archer") {
			enemies.emplace_back(std::make_unique<Archer>(spawnPosition.x, spawnPosition.y, "enemy"));
		}
	}

}

void Distribution::reset_potion() {
	enemyLevel.decrease_potion_level(10);
}