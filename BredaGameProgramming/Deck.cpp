#include "Deck.h"
#include "Cards.h"
#include <iostream>
#include <random>

Deck::Deck() {

}



void Deck::card_shuffle(std::vector<std::unique_ptr<Card>> &cards) {
	bool alreadyInDeck = false;
	int randomCard;
	for (int i; i < 5; i++) {
		if (selectedCards[i] == -1) {
			std::srand(std::time(0));

			do {
				randomCard = std::rand() % cards.size();
				for (int j; j < 5; j++) {
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
	for (int i; i < 5; i++) {
		cards[selectedCards[i]];
	}


}