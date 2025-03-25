#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
class Game {
public:

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

	void instantiate_characters();

	void update_screen();

	void poll_events();


	void running();

	Game();





};