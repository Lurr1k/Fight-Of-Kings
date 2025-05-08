#pragma once
#include "Character.h"
#include "Cards.h"
#include "Deck.h"
#include "Potion.h"
#include "Distribution.h"
#include "Screens.h"
class Game {
private:
	sf::Clock clock;
	sf::Texture backgroundTexture;
	sf::Texture helpPageTexture;
	sf::Texture helpPage2Texture;
	sf::Texture startPageTexture;
	sf::Texture endPageTexture;
	std::optional<sf::Sprite> helpPageBackground;
	std::optional<sf::Sprite> helpPage2Background;
	std::optional<sf::Sprite> startPageBackground;
	std::optional<sf::Sprite> endPageBackground;
	std::optional<sf::Sprite> background;
	std::string windowTitle;
	sf::VideoMode resolution;
	std::vector<std::unique_ptr<Character>> heroes;
	std::vector<std::unique_ptr<Character>> enemies;
	std::vector<std::unique_ptr<Card>> cards;
	sf::RenderWindow window;
	Deck decky;
	Potion potion;
	Distribution distribution;
	StartingScreen startingScreen;
	HelpScreen helpScreen;
	EndScreen endScreen;
	bool gameRunning = false;
	bool helpPage = false;
	bool helpPage2 = false;
	bool endPage = false;
	bool startPage = true;

	

public:

	// Initialises the window
	void init_window();

	// Loads the background textures for all of the screens
	void load_background();

	// Instantiates the towers and cards for the game's start
	void instantiate_characters();

	// Updates the screen, displaying all of the screens and characters
	void update_screen();

	// Scans for events and performs their consequences
	void poll_events();

	// Performed each time the game starts, resets everything on the game screen and switches to the game screen
	void start_game();

	// The general game loop
	void running();

	// Checks if any of the sides has lost all three towers, and if that is the case, finishes the game and switches to the end screen.
	void check_if_game_over();

	// Game constructor, initialises the window, the sounds and loads the backgrounds
	Game();





};