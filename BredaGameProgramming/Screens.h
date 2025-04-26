#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Text.h"

// Screen with three big buttons
// The buttons are start and help
// Start button launches the game
// Help button directs to the help screen, which explains the rules and how to play, etc 
// Once the game ends (no towers left on one side) the final screen is displayed (check_if_game_over)
// States the winner and offers to return to the main screen

class StartingScreen {
private:
	sf::RectangleShape startButton;
	sf::RectangleShape helpButton;
	Text startButtonSign = Text("Start", 30);
	Text helpButtonSign = Text("Help", 30);
	sf::FloatRect startButtonBoundaries;
	sf::FloatRect helpButtonBoundaries;
	bool startButtonHovered;
	bool helpButtonHovered;
public:
	StartingScreen();

	void draw_starting_screen(sf::RenderWindow& window);
	

	bool start_hovered(sf::RenderWindow& window);

	bool help_hovered(sf::RenderWindow& window);

	bool detect_button_hovered(sf::FloatRect boundaries, sf::RenderWindow& window);

};