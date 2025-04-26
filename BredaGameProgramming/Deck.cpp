#include "Deck.h"
#include "Cards.h"
#include "Character.h"
#include <iostream>
#include <random>
#include "Potion.h"

Deck::Deck() {
	deckRectangle = sf::FloatRect({ 150, 849 }, { 450, 111 });
	for (int i = 0; i < 5; i++) {
		selectedCards[i] = -1;
	}
}



void Deck::card_shuffle(std::vector<std::unique_ptr<Card>> &cards) {
	int nextCard;
	int loopCount;
	std::srand(std::time(0));
	for (int i = 0; i < 5; i++) {
		nextCard = 0;
		if (selectedCards[i] == -1) {
			loopCount = 0;

			while ((in_deck(nextCard) or (nextCard == previouslyPlacedCard)) and nextCard < cards.size()){
				nextCard += 1;
			}

			selectedCards[i] = nextCard;
			cards[nextCard]->set_initial_position(215 + (i * 81), 900);
		}
	}		
}

void Deck::display_deck(sf::RenderWindow &window, std::vector<std::unique_ptr<Card>> &cards) {
	// for i in selected cards, display every card with a gap of 81 pixels on the x-axis
	int cardsIndex;
	for (int i = 0; i < 5; i++) {
		cardsIndex = selectedCards[i];
		if (cardsIndex != -1) {

			cards[cardsIndex]->draw_card(window);
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
				std::cout << selectedCards[i];
				selectedCards[i] = -1;
			}
		}
	}
}

void Deck::spawn_or_return(std::vector<std::unique_ptr<Card>>& cards, std::vector<std::unique_ptr<Character>>& heroes, Potion &potion) {
	sf::Vector2f cardPos;
	for (int i = 0; i < 5; i++) {
		int index = selectedCards[i];
		if (index != -1) {
			cardPos = cards[index]->get_position();

			if (is_hovered(cardPos) or (cards[index]->get_cost() > potion.get_potion_level()) or (cardPos.y < 510)) {
				cards[index]->return_to_position();
			}
			else {
				if (cards[index]->get_type() == "goblin") {
					heroes.emplace_back(std::make_unique<Goblin>(cardPos.x, cardPos.y, "hero"));
				}
				else if (cards[index]->get_type() == "giant") {
					heroes.emplace_back(std::make_unique<Giant>(cardPos.x, cardPos.y, "hero"));
				}
				previouslyPlacedCard = index;
				potion.decrease_potion_level(cards[index]->get_cost());
				cards[index]->return_to_position();
				remove_from_deck(index);
				card_shuffle(cards);
			}
		}
	}
}

int Deck::get_selected_card(int index) {
	return selectedCards[index];
}