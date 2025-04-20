#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"


class Potion {
private:
	float potionLevel;
	sf::RectangleShape potionBarBackground;
	sf::RectangleShape potionLevelBar;
public:

	Potion();

	void increase_potion_level();

	void decrease_potion_level();

	void display_potion_level();



};