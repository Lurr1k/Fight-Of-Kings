#include "Deck.h"
#include "Cards.h"
#include <iostream>
#include <random>

Deck::Deck() {

}

void Deck::card_shuffle(std::vector<std::unique_ptr<Card>> cards) {
	int selectedCards[5];
	for (int i; i < 5; i++) {
		
		std::srand(std::time(0));
		int randomCard = std::rand() % cards.size();


		


		selectedCards[i] = 1;
	}
}