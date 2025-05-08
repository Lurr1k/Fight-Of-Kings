#pragma once
#include "Text.h"
#include <iostream>

class Button {
private:
	sf::RectangleShape button;
	Text buttonSign;
	sf::FloatRect buttonBoundaries;
public:
	Button(sf::Vector2f coordinates, std::string text);

	// Displays the button
	void display_button(sf::RenderWindow& window);

	// Returns whether the button is currently hovered over
	bool detect_button_hovered(sf::RenderWindow& window);

	// Scans whether the button is hovered
	void scan_hovered(sf::RenderWindow& window);

};