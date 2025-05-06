#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Text.h"
#include "Button.h"
#include "Crowns.h"



class StartingScreen {
private:
	Button startButton = Button({ 375, 490 }, "Start");
	Button helpButton = Button({ 375, 640 }, "Help");

public:

	// Displays the starting screen
	void draw_starting_screen(sf::RenderWindow& window);
	
	// Returns whether the start button is hovered
	bool start_hovered(sf::RenderWindow& window);

	// scans whether any of the buttons are hovered
	void scan_hovered(sf::RenderWindow& window);

	// Returns whether the help button is hovered
	bool help_hovered(sf::RenderWindow& window);


};

class HelpScreen {
private:
	Button backButton = Button({ 225, 800 }, "Back"); 
	Button nextButton = Button({ 525, 800 }, ">>");
public:
	// Displays the help screen
	void draw_help_screen(sf::RenderWindow& window);
	// Scans whether any of the buttons are hovered
	void scan_hovered(sf::RenderWindow& window);
	// Returns whether the back button is hovered
	bool back_hovered(sf::RenderWindow& window);
	// Returns whether the next button is hovered
	bool next_hovered(sf::RenderWindow& window);


};

class EndScreen {
private:
	Button returnButton = Button({ 375, 770 }, "Return");
	std::vector<std::unique_ptr<Crown>> crowns;
	int destroyedTowers;
	int lostTowers;
	Text resultSign = Text("You ___", 50);
	sf::SoundBuffer endBuffer;
	sf::Sound endSound = sf::Sound(endBuffer);
public: 
	// Displays the help screen
	void draw_end_screen(sf::RenderWindow& window);

	// Scans whether any of the buttons are hovered
	void scan_hovered(sf::RenderWindow& window);

	// Returns whether the return button is hovered
	bool return_hovered(sf::RenderWindow& window);

	//Creates the crowns for the amounts of points each side has earned
	void crown_creation(int dTowers, int lTowers);

	//Removes all the crowns
	void clear_crowns();

	//Sets the result text 
	void set_result_text();
};
