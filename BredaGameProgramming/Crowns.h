#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>


class Crown {
private:
	sf::Texture texture;
	sf::Sprite crown = sf::Sprite(texture);
	std::string texturePath;

public:
	Crown();

	// Displays the crown
	void display_crown(sf::RenderWindow& window);

	// Sets the crown's position at the given coordinates
	void set_position(sf::Vector2f coordinates);
};