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
	Button helpButton = Button({ 375, 690 }, "Help");

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
	void draw_end_screen(sf::RenderWindow& window);

	void scan_hovered(sf::RenderWindow& window);

	bool return_hovered(sf::RenderWindow& window);

	void crown_creation(int dTowers, int lTowers);

	void clear_crowns();

	void set_result_text();
};
