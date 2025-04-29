#pragma once
#include <SFML/Graphics.hpp>
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
	sf::Texture startPageTexture;
	std::optional<sf::Sprite> helpPageBackground;
	std::optional<sf::Sprite> startPageBackground;
	std::optional<sf::Sprite> background;
	unsigned int height;
	unsigned int width;
	int frameLimit;
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
	bool gameRunning = false;
	bool helpPage = false;

public:

	void init_window();

	void load_background();

	void instantiate_characters();

	void update_screen();

	void poll_events();

	void start_game();

	void running();

	Game();





};