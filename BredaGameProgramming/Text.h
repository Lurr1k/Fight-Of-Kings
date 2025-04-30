#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class Text {
private:
	const std::string FONTADDRESS = "fonts/Arial.ttf";
	sf::Font font;
	float fontSize;
	std::string textToDisplay;
	sf::Vector2f textPosition;
	sf::Text sign;
public:
	Text(std::string text, float size);

	void update_text(std::string text);

	void display_text(sf::RenderWindow& window);

	void set_position(sf::Vector2f coordinates);

	void set_colour(sf::Color colour);
};