#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
class Game {
public:
	sf::Clock clock;
	sf::Texture backgroundTexture;
	sf::Sprite background;
	unsigned int height;
	unsigned int width;
	int frameLimit;
	std::string windowTitle;
	sf::VideoMode resolution;
	std::vector<std::unique_ptr<Character>> heroes;
	std::vector<std::unique_ptr<Character>> enemies;
	Giant character;

	sf::RenderWindow window;

	void init_window();

	void load_background();

	void instantiate_characters();

	void update_screen();

	void poll_events();


	void running();

	Game();





};