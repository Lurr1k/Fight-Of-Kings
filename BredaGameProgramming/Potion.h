#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Text.h"

class Potion {
private:
	float potionLevel;
	sf::RectangleShape potionBarBackground;
	sf::RectangleShape potionLevelBar;
	sf::CircleShape levelCircle;
	Text levelSign = Text("", 23.0);
public:

	Potion();
	// Increases the potion level
	void increase_potion_level(float& deltaTime);
	// Decreases the potion level
	void decrease_potion_level(float amount);
	// Displays the potion level
	void display_potion(sf::RenderWindow& window);

	// Returns the current potion level
	float get_potion_level();



};