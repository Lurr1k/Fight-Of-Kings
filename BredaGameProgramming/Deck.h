#pragma once
#include "Cards.h"
#include "Character.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Deck {
private:
	sf::FloatRect deckRectangle;
	int selectedCards[5];
public:
	
	Deck();

	void card_shuffle(std::vector<std::unique_ptr<Card>> &cards);

	void display_deck(sf::RenderWindow& window, std::vector<std::unique_ptr<Card>> &cards);

	bool in_deck(int index);

	bool is_hovered(sf::Vector2f position);

	void remove_from_deck(int index);

	int get_selected_card(int index);

	void spawn_or_return(std::vector<std::unique_ptr<Card>>& cards, std::vector<std::unique_ptr<Character>>& heroes);
};

