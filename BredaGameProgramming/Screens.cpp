#include "Screens.h"



// Displays the starting screen
void StartingScreen::draw_starting_screen(sf::RenderWindow& window) {
	startButton.display_button(window);
	helpButton.display_button(window);
}

// Returns whether the start button is hovered
bool StartingScreen::start_hovered(sf::RenderWindow& window) {

	return startButton.detect_button_hovered(window);
}
// Returns whether the help button is hovered
bool StartingScreen::help_hovered(sf::RenderWindow& window) {

	return helpButton.detect_button_hovered(window);
}
// Scans whether any of the buttons are hovered and lights up the buttons if they are
void StartingScreen::scan_hovered(sf::RenderWindow& window) {
	startButton.scan_hovered(window);
	helpButton.scan_hovered(window);
}

// Displays the help screen
void HelpScreen::draw_help_screen(sf::RenderWindow& window) {
	backButton.display_button(window);
	nextButton.display_button(window);
}

// Returns whether the back button is hovered
bool HelpScreen::back_hovered(sf::RenderWindow& window) {
	return backButton.detect_button_hovered(window);
}
// Returns whether the next button is hovered
bool HelpScreen::next_hovered(sf::RenderWindow& window) {
	return nextButton.detect_button_hovered(window);
}

// Scans whether any of the buttons are hovered and lights up the buttons if they are
void HelpScreen::scan_hovered(sf::RenderWindow& window) {
	backButton.scan_hovered(window);
	nextButton.scan_hovered(window);
}

// Displays the end screen
void EndScreen::draw_end_screen(sf::RenderWindow&  window) {
	for (auto& crown : crowns) {
		crown->display_crown(window);
	}
	returnButton.display_button(window);
	resultSign.display_text(window);
}

// Scans whether any of the buttons are hovered and lights up the buttons if they are
void EndScreen::scan_hovered(sf::RenderWindow& window) {
	returnButton.scan_hovered(window);
}

// Returns whether the back button is hovered
bool EndScreen::return_hovered(sf::RenderWindow& window) {
	return returnButton.detect_button_hovered(window);
}

// Creates the crowns for the amounts of points each side has earned
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

// Removes all the crowns
void EndScreen::clear_crowns() {
	crowns.clear();
}

// Sets the result text 
void EndScreen::set_result_text() {
	std::string soundPath;
	if (destroyedTowers > lostTowers) {
		resultSign.update_text("You won!");
		resultSign.set_colour(sf::Color::Green);
		soundPath = "sounds/happy.mp3";
	}
	else {
		resultSign.update_text("You lost!");
		resultSign.set_colour(sf::Color::Red);
		soundPath = "sounds/sad.mp3";
	}
	endBuffer.loadFromFile(soundPath);
	endSound.setBuffer(endBuffer);
	endSound.setVolume(10);
	endSound.play();

	resultSign.set_position({ 375, 400 });
}