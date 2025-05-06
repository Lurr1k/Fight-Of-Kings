#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Character.h"
#include "Cards.h"
#include "Deck.h"
#include "Potion.h"
#include "Distribution.h"
#include "Screens.h"
#include "Crowns.h"
class Game {
private:

	sf::Clock clock;
	sf::Texture backgroundTexture;
	sf::Texture helpPageTexture;
	sf::Texture startPageTexture;
	sf::Texture endPageTexture;
	std::optional<sf::Sprite> helpPageBackground;
	std::optional<sf::Sprite> startPageBackground;
	std::optional<sf::Sprite> endPageBackground;
	std::optional<sf::Sprite> background;
	sf::Music backgroundMusic;
	sf::SoundBuffer slashBuffer;
	sf::Sound slashSound = sf::Sound(slashBuffer);
	sf::SoundBuffer huhBuffer;
	sf::Sound huhSound = sf::Sound(huhBuffer);
	sf::SoundBuffer bookBuffer;
	sf::Sound bookSound = sf::Sound(bookBuffer);
	unsigned int height;
	unsigned int width;
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
	Button muteButton = Button({ 375,0 }, "Mute music");
	bool gameRunning = false;
	bool helpPage = false;
	bool endPage = false;
	bool startPage = true;
	enum levels {START, HELP, GAME, END};

	

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