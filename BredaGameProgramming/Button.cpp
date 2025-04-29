#include "Button.h"
#include "Text.h"
#include <iostream>


Button::Button(sf::Vector2f coordinates, std::string text) : buttonSign(text, 30) {
	button.setSize({ 100, 50 });
	button.setFillColor(sf::Color::Yellow);
	button.setOrigin(button.getGeometricCenter());
	button.setPosition(coordinates);
	buttonBoundaries = button.getGlobalBounds();
	buttonSign.set_position(coordinates);
	buttonHovered = false;
}


bool Button::detect_button_hovered(sf::RenderWindow& window) {
	sf::Vector2i intCoords = sf::Mouse::getPosition(window);
	sf::Vector2f floatCoords = { static_cast<float>(intCoords.x), static_cast<float>(intCoords.y) };
	bool hovered = false;
	if (buttonBoundaries.contains(floatCoords)) {
		hovered = true;
	}
	return hovered;
}

void Button::scan_hovered(sf::RenderWindow& window) {
	if (detect_button_hovered(window)) {
		buttonHovered = true;
		button.setFillColor(sf::Color::White);

	}
	else {
		buttonHovered = false;
		button.setFillColor(sf::Color::Yellow);

	}
}

void Button::display_button(sf::RenderWindow &window){
	window.draw(button);
	buttonSign.display_text(window);
}