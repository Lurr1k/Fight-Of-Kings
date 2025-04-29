#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Text.h"
#include "Button.h"

// Screen with three big buttons
// + The buttons are start and help 
// + Start button launches the game 
// + Help button directs to the help screen, which explains the rules and how to play, etc 
// Once the game ends (no towers left on one side) the final screen is displayed (check_if_game_over)
// States the winner and offers to return to the main screen

class StartingScreen {
private:
	Button startButton = Button({ 375, 430 }, "Start");
	Button helpButton = Button({ 375, 510 }, "Help");

public:
	StartingScreen();

	void draw_starting_screen(sf::RenderWindow& window);
	

	bool start_hovered(sf::RenderWindow& window);

	void scan_hovered(sf::RenderWindow& window);

	bool help_hovered(sf::RenderWindow& window);


};

class HelpScreen {
private:
	Button backButton = Button({ 375, 770 }, "Back"); 
public:

	void draw_help_screen(sf::RenderWindow& window);

	void scan_hovered(sf::RenderWindow& window);

	bool back_hovered(sf::RenderWindow& window);


};