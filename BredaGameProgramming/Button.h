#pragma once
#include "Text.h"
#include <iostream>

class Button {
private:
	sf::RectangleShape button;
	Text buttonSign;
	sf::FloatRect buttonBoundaries;
	bool buttonHovered;
public:
	Button(sf::Vector2f coordinates, std::string text);

	void display_button(sf::RenderWindow& window);

	bool detect_button_hovered(sf::RenderWindow& window);

	void scan_hovered(sf::RenderWindow& window);

};