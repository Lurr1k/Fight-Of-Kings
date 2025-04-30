#include "Screens.h"
#include "Text.h"
#include "Button.h"
#include "Crowns.h"

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

void EndScreen::draw_end_screen(sf::RenderWindow & window) {
	for (int i = 0; i < crowns.size(); i++) {
		crowns[i]->display_crown(window);
	}
	returnButton.display_button(window);
	resultSign.display_text(window);
}

void EndScreen::scan_hovered(sf::RenderWindow& window) {
	returnButton.scan_hovered(window);
}

bool EndScreen::return_hovered(sf::RenderWindow& window) {
	return returnButton.detect_button_hovered(window);
}

void EndScreen::crown_creation(int dTowers, int lTowers) {
	destroyedTowers = dTowers;
	lostTowers = lTowers;


	for (float i = 0; i < lostTowers; i++) {
		crowns.emplace_back(std::make_unique<Crown>());
		crowns[i]->set_position({ (140 + (i * 195)), 210 });
	}
	for (float i = 0; i < destroyedTowers; i++) {
		crowns.emplace_back(std::make_unique<Crown>());
		crowns[i + lostTowers]->set_position({ (140 + (i * 195)), 600 });
	}
}

void EndScreen::clear_crowns() {
	crowns.clear();
}

void EndScreen::set_result_text() {
	if (destroyedTowers > lostTowers) {
		resultSign.update_text("You won!");
		resultSign.set_colour(sf::Color::Green);
	}
	else {
		resultSign.update_text("You lost!");
		resultSign.set_colour(sf::Color::Red);
	}
	
	resultSign.set_position({ 375, 400 });
}