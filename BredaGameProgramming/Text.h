#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Text {
private:
	const std::string FONTADDRESS = "fonts/Sacomin.otf";
	sf::Font font;
	float fontSize;
	std::string textToDisplay;
	sf::Vector2f textPos;
	sf::Text sign;
public:
	Text(std::string text, float size);

	// Updates the text of the text sign
	void update_text(std::string text);

	// Displays the text on the screen
	void display_text(sf::RenderWindow& window);

	// Sets the text's position on the screen
	void set_position(sf::Vector2f coordinates);

	// Sets the text colour 
	void set_colour(sf::Color colour);
};