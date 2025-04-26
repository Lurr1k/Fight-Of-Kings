#include "Screens.h"
#include "Text.h"

StartingScreen::StartingScreen() {

	startButton.setSize({ 100, 50 });
	startButton.setFillColor(sf::Color::Yellow);
	startButton.setOrigin(helpButton.getGeometricCenter());
	startButton.setPosition({375, 450});
	startButtonBoundaries = helpButton.getGlobalBounds();
	startButtonSign.set_position(375, 450);
	startButtonHovered = false;

	helpButton.setSize({ 100, 50 });
	helpButton.setFillColor(sf::Color::Yellow);
	helpButton.setOrigin(helpButton.getGeometricCenter());
	helpButton.setPosition({375, 510});
	helpButtonBoundaries = helpButton.getGlobalBounds();
	helpButtonSign.set_position(375, 510);
	helpButtonHovered = false;


}

void StartingScreen::draw_starting_screen(sf::RenderWindow& window) {
	window.draw(helpButton);
	window.draw(startButton);
	helpButtonSign.display_text(window);
	startButtonSign.display_text(window);

}


bool StartingScreen::detect_button_hovered(sf::FloatRect boundaries, sf::RenderWindow& window) {
	sf::Vector2i intCoords = sf::Mouse::getPosition(window);
	sf::Vector2f floatCoords = { static_cast<float>(intCoords.x), static_cast<float>(intCoords.y) };
	bool hovered = false;
	if (boundaries.contains(floatCoords)) {
		hovered = true;
	}
	return hovered;
}

bool StartingScreen::start_hovered(sf::RenderWindow& window) {
	if (detect_button_hovered(startButtonBoundaries, window)) {
		startButtonHovered = true;
		startButton.setFillColor(sf::Color::White);
	}
	else {
		startButtonHovered = false;
		startButton.setFillColor(sf::Color::Yellow);
	}
	return startButtonHovered;
}

bool StartingScreen::help_hovered(sf::RenderWindow& window) {
	if (detect_button_hovered(helpButtonBoundaries, window)) {
		helpButtonHovered = true;
		helpButton.setFillColor(sf::Color::White);
	}
	else {
		helpButtonHovered = false;
		helpButton.setFillColor(sf::Color::Yellow);
	}
	return helpButtonHovered;
}