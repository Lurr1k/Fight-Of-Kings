#pragma once
#include "Cards.h"
#include "Character.h"
#include <iostream>
#include <random>
#include "Potion.h"

class Deck {
private:
	sf::FloatRect deckRectangle;
	int selectedCards[5];
	int previouslyPlacedCard;
	float timer;
	bool incorrectPlacement;
	bool lowPotion;
	Text errorSign = Text("You ___", 30);
public:
	
	Deck();

	// Shuffles the cards
	void card_shuffle(std::vector<std::unique_ptr<Card>>& cards);

	// Displays the deck 
	void display_deck(sf::RenderWindow& window, std::vector<std::unique_ptr<Card>>& cards);

	// Returns whether a card of an input index is currently in the deck
	bool in_deck(int index);

	// Returns whether the input position is over the deck
	bool is_hovered(sf::Vector2f Pos);

	// Removes the card of input index from the deck
	void remove_from_deck(int index);

	// Returns the card that is currently selected
	int get_selected_card(int index);

	// Determines whether the card spawns the character or returns 
	// to the deck depending on potionLevel and placement position
	// And manages the corresponding errors
	void spawn_or_return(std::vector<std::unique_ptr<Card>>& cards, std::vector<std::unique_ptr<Character>>& heroes, Potion& potion, int cardIndex);

	// Updates the error timer
	void update_timer(float& deltaTime);
};

