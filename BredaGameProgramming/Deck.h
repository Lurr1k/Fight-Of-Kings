#pragma once
#include "Cards.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Deck {
private:
	sf::FloatRect deckRectangle;
	int selectedCards[5] = {-1,-1,-1,-1,-1};
public:
	
	Deck();

	void card_shuffle(std::vector<std::unique_ptr<Card>> &cards);

	void display_deck(sf::RenderWindow& window, std::vector<std::unique_ptr<Card>> &cards);

};

