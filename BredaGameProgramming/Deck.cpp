#include "Deck.h"
#include "Cards.h"
#include "Character.h"
#include <iostream>
#include <random>

Deck::Deck() {
	deckRectangle = sf::FloatRect({ 150, 849 }, { 450, 111 });
}



void Deck::card_shuffle(std::vector<std::unique_ptr<Card>> &cards) {
	bool alreadyInDeck = false;
	int randomCard;
	int loopCount;
	for (int i = 0; i < 5; i++) {
		if (selectedCards[i] == -1) {
			std::srand(std::time(0));
			loopCount = 0;
			do {
				loopCount += 1;
				randomCard = std::rand() % cards.size();
				for (int j = 0; j < 5; j++) {
					if (randomCard == selectedCards[j]) {
						alreadyInDeck = true;
					}
				}
			} while (alreadyInDeck and (loopCount < 50));

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

			cards[selectedCards[i]]->set_initial_position(215 + (i * 81), 900);

			cards[selectedCards[i]]->draw_card(window);
		}
	}
}

bool Deck::in_deck(int index) {
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
	if (in_deck(index)) {
		for (int i = 0; i < 5; i++) {
			if (selectedCards[i] == index) {
				selectedCards[i] = -1;
				std::cout << selectedCards[i];
			}
		}
	}
}

void Deck::spawn_or_return(std::vector<std::unique_ptr<Card>>& cards, std::vector<std::unique_ptr<Character>>& heroes) {
	sf::Vector2f cardPos;
	for (int i = 0; i < 5; i++) {
		int index = selectedCards[i];
		if (in_deck(index) and (index != -1)) {
			cardPos = cards[index]->get_position();

			if (is_hovered(cardPos)) {
				cards[index]->return_to_position();
			}
			else {
				if (cards[index]->get_type() == "goblin") {
					heroes.emplace_back(std::make_unique<Goblin>(cardPos.x, cardPos.y, "hero"));
				}

				remove_from_deck(index);
				cards.erase(cards.begin() + index);
			}
		}
	}
}