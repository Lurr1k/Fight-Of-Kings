#include "Distribution.h"



Distribution::Distribution() {
	xLimit = 750;
	yLimit = 450;
	enemySide = sf::FloatRect({ 0,0 }, { xLimit, yLimit });
	randomTime = 5;
}

// Generates the spawn location for the enemy characters
sf::Vector2f Distribution::generate_spawn_location(std::vector<std::unique_ptr<Character>>& heroes) {
	float generatedX;
	float generatedY;
	sf::Vector2f generatedPos;
	int characterCount = 0;
	int rightCount = 0;
	int leftCount = 0;
	for (auto& hero : heroes) {
		if (hero->get_name() != "Tower") {
			characterCount += 1;
			if ((hero->get_position()).x > 375) {
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

// Checks whether the timer allows to spawn enemies and regenerates the pseudorandom time pause
bool Distribution::timing_correct(float
	
	
	deltaTime) {
	timer += deltaTime;
	bool timing = false;
	if (timer >= randomTime) {
		timer = 0;
		timing = true;
		randomTime = 4 + (rand() % 5);
	}
	else {
		timing = false;
	}
	return timing;
}

// Chooses the type of the enemy to spawn
std::string Distribution::choose_type() {
	std::string chosenType;
	float potionLevel = enemyLevel.get_potion_level();
	if (potionLevel < 4 and potionLevel >= 2) {
		chosenType = "goblin";
		enemyLevel.decrease_potion_level(2);
	}
	else if (potionLevel < 6 and potionLevel >= 4) {
		chosenType = "archer";
		enemyLevel.decrease_potion_level(3);
	}
	else if (potionLevel <= 10 and potionLevel >= 6) {
		chosenType = "giant";
		enemyLevel.decrease_potion_level(5);
	}

	return chosenType;
}

// Spawns the enemies on the enemy side
void Distribution::spawn_enemies(float& deltaTime, std::vector<std::unique_ptr<Character>>& heroes, std::vector<std::unique_ptr<Character>>& enemies) {
	enemyLevel.increase_potion_level(deltaTime);
	std::string chosenType;
	sf::Vector2f spawnPos;
	if (timing_correct(deltaTime)) {
		chosenType = choose_type();
		spawnPos = generate_spawn_location(heroes);
		if (chosenType == "goblin") {
			enemies.emplace_back(std::make_unique<Goblin>(spawnPos.x, spawnPos.y, "enemy"));
		}
		else if (chosenType == "giant") {
			enemies.emplace_back(std::make_unique<Giant>(spawnPos.x, spawnPos.y, "enemy"));
		}
		else if (chosenType == "archer") {
			enemies.emplace_back(std::make_unique<Archer>(spawnPos.x, spawnPos.y, "enemy"));
		}
	}

}

// Resets the potion level for the enemy
void Distribution::reset_potion() {
	enemyLevel.decrease_potion_level(10);
}