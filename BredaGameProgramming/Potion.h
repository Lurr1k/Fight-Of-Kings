#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"


class Potion {
private:
	float potionLevel;
	sf::RectangleShape potionBarBackground;
	sf::RectangleShape potionLevelBar;
	sf::CircleShape levelCircle;
public:

	Potion();

	void increase_potion_level(float &deltaTime);

	void decrease_potion_level(float amount);

	void display_potion(sf::RenderWindow& window);

	float get_potion_level();



};