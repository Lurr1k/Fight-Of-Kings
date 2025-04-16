#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Cards.h"
#include "Deck.h"
class Game {
public:
	sf::Clock clock;
	sf::Texture backgroundTexture;
	std::optional<sf::Sprite> background;
	unsigned int height;
	unsigned int width;
	int frameLimit;
	std::string windowTitle;
	sf::VideoMode resolution;
	std::vector<std::unique_ptr<Character>> heroes;
	std::vector<std::unique_ptr<Character>> enemies;
	std::vector<std::unique_ptr<Card>> cards;
	Giant character;
	sf::RenderWindow window;
	sf::FloatRect cardDeck;
	Deck decky;

	void init_window();

	void load_background();

	void instantiate_characters();

	void update_screen();

	void poll_events();

	void spawn_or_return();


	void running();

	Game();





};