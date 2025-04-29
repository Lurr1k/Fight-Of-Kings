#include "Screens.h"
#include "Text.h"
#include "Button.h"

StartingScreen::StartingScreen() {


}

void StartingScreen::draw_starting_screen(sf::RenderWindow& window) {
	startButton.display_button(window);
	helpButton.display_button(window);
}


bool StartingScreen::start_hovered(sf::RenderWindow& window) {

	return startButton.detect_button_hovered(window);
}

bool StartingScreen::help_hovered(sf::RenderWindow& window) {

	return helpButton.detect_button_hovered(window);
}

void StartingScreen::scan_hovered(sf::RenderWindow& window) {
	startButton.scan_hovered(window);
	helpButton.scan_hovered(window);
}

void HelpScreen::draw_help_screen(sf::RenderWindow& window) {
	backButton.display_button(window);
}

bool HelpScreen::back_hovered(sf::RenderWindow& window) {
	return backButton.detect_button_hovered(window);
}

void HelpScreen::scan_hovered(sf::RenderWindow& window) {
	backButton.scan_hovered(window);
}