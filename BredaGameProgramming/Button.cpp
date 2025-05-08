#include "Button.h"



Button::Button(sf::Vector2f coordinates, std::string text) : buttonSign(text, 30) {
	button.setSize({ 250, 75 });
	button.setFillColor(sf::Color::Yellow);
	button.setOrigin(button.getGeometricCenter());
	button.setPosition(coordinates);
	buttonBoundaries = button.getGlobalBounds();
	buttonSign.set_position(coordinates);
}

// Detects whether the button is currently hovered over
bool Button::detect_button_hovered(sf::RenderWindow& window) {
	sf::Vector2i intCoords = sf::Mouse::getPosition(window);
	sf::Vector2f floatCoords = { static_cast<float>(intCoords.x), static_cast<float>(intCoords.y) };
	bool hovered = false;
	if (buttonBoundaries.contains(floatCoords)) {
		hovered = true;
	}
	return hovered;
}
// Lights the buttons up based on whether they are hovered
void Button::scan_hovered(sf::RenderWindow& window) {
	if (detect_button_hovered(window)) {
		button.setFillColor(sf::Color::White);

	}
	else {
		button.setFillColor(sf::Color::Yellow);

	}
}
// Displays the button
void Button::display_button(sf::RenderWindow& window){
	window.draw(button);
	buttonSign.display_text(window);
}