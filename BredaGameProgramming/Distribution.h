#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
// Spawn on the same side as the character. If there is more than one - one with more characters. 
//Generate based on times and current elixir levels
//If no active enemies exist, spawn a character to attack the towers

class Distribution {
private:
public:

	Distribution();


	sf::Vector2f generate_spawn_location();




};