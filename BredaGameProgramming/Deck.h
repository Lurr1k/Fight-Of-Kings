#pragma once
#include "Cards.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Deck {
private:
	sf::FloatRect deckRectangle;

public:
	
	Deck();

	void card_shuffle(std::vector<std::unique_ptr<Card>> cards);

};

