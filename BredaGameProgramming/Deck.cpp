#include "Deck.h"
#include "Cards.h"
#include <iostream>
#include <random>

Deck::Deck() {
	deckRectangle = sf::FloatRect({ 150, 849 }, { 450, 111 });
}



void Deck::card_shuffle(std::vector<std::unique_ptr<Card>> &cards) {
	bool alreadyInDeck = false;
	int randomCard;
	for (int i = 0; i < 5; i++) {
		if (selectedCards[i] == -1) {
			std::srand(std::time(0));

			do {
				randomCard = std::rand() % cards.size();
				for (int j = 0; j < 5; j++) {
					if (randomCard == selectedCards[j]) {
						alreadyInDeck = true;
					}
				}
			} while (alreadyInDeck);

			selectedCards[i] = randomCard;
		}
	}		
}

void Deck::display_deck(sf::RenderWindow &window, std::vector<std::unique_ptr<Card>> &cards) {
	// for i in selected cards, display every card with a gap of 81 pixels on the x-axis
	int cardsIndex;
	for (int i = 0; i < 5; i++) {
		cardsIndex = selectedCards[i];
		if (cardsIndex != -1) {
			cards[selectedCards[i]]->set_card_position(215 + (i * 81), 900);
			cards[selectedCards[i]]->draw_card(window);
		}
	}
}

bool Deck::check_if_in_deck(int index) {
	for (int i = 0; i < 5; i++) {
		if (selectedCards[i] == index) {
			return true;
		}
	}
	return false;
}

bool Deck::is_hovered(sf::Vector2f position) {

	if (deckRectangle.contains(position)) {
		return true;
	}
	else {
		return false;
	}
}

void Deck::remove_from_deck(int index){
	if (check_if_in_deck(index)) {
		for (int i = 0; i < 5; i++) {
			if (selectedCards[i] == index) {
				selectedCards[i] = -1;
			}
		}
	}
}