#pragma once
#include "Character.h"
#include "Cards.h"
#include "Deck.h"
#include "Potion.h"
#include "Distribution.h"
#include "Screens.h"
class Game {
private:
	Audio audio;
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

	void init_window();
	
	void init_sounds();

	void load_background();

	void instantiate_characters();

	void update_screen();

	void poll_events();

	void start_game();

	void running();

	void check_if_game_over();

	void mute_music();

	Game();





};