#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"


class Crown {
private:
	sf::Texture texture;
	sf::Sprite crown = sf::Sprite(texture);
	std::string texturePath;

public:
	Crown();

	void display_crown(sf::RenderWindow &window);

	void set_position(sf::Vector2f coordinates);
};