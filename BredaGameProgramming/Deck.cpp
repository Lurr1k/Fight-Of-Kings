#include "Deck.h"


Deck::Deck() {
	deckRectangle = sf::FloatRect({ 150, 849 }, { 450, 111 });
	for (int i = 0; i < 5; i++) {
		selectedCards[i] = -1;
	}
	timer = 5;
	errorSign.set_position({ 180, 600 });
	errorSign.set_colour(sf::Color::Transparent);
}



void Deck::card_shuffle(std::vector<std::unique_ptr<Card>>& cards) {
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

void Deck::display_deck(sf::RenderWindow& window, std::vector<std::unique_ptr<Card>>& cards) {
	int cardsIndex;
	for (int i = 0; i < 5; i++) {
		cardsIndex = selectedCards[i];
		if (cardsIndex != -1) {

			cards[cardsIndex]->draw_card(window);
		}
	}
	errorSign.display_text(window);

	if (timer < 5) {
		errorSign.set_colour(sf::Color::Red);
	}
	else {
		errorSign.set_colour(sf::Color::Transparent);
		
	}
	
}

bool Deck::in_deck(int index) {
	bool inDeck = false;
	for (int i = 0; i < 5; i++) {
		if (selectedCards[i] == index) {
			inDeck = true;
		}
	}
	return inDeck;
}

bool Deck::is_hovered(sf::Vector2f pos) {
	bool isHovered = false;
	if (deckRectangle.contains(pos)) {
		isHovered = true;
	}
	return isHovered;
}

void Deck::remove_from_deck(int index){
	if (in_deck(index)) {
		for (int i = 0; i < 5; i++) {
			if (selectedCards[i] == index) {

				selectedCards[i] = -1;
			}
		}
	}
}

void Deck::spawn_or_return(std::vector<std::unique_ptr<Card>>& cards, std::vector<std::unique_ptr<Character>>& heroes, Potion& potion, int cardIndex) {
	sf::Vector2f cardPos;
	int index = cardIndex;
	if (index != -1) {
		cardPos = cards[index]->get_position();

		if (is_hovered(cardPos) or (cardPos.y < 510)) {
			incorrectPlacement = true;
			errorSign.update_text("You can't place the card there!");
			cards[index]->return_to_position();
			timer = 0;
		}
		else if (cards[index]->get_cost() > potion.get_potion_level()) {
			lowPotion = true;
			errorSign.update_text("You need more potion to spawn this entity!");
			cards[index]->return_to_position();
			timer = 0;
		}

		else {
			errorSign.update_text("");
			if (cards[index]->get_type() == "goblin") {
				heroes.emplace_back(std::make_unique<Goblin>(cardPos.x, cardPos.y, "hero"));
			}
			else if (cards[index]->get_type() == "giant") {
				heroes.emplace_back(std::make_unique<Giant>(cardPos.x, cardPos.y, "hero"));
			}
			else if (cards[index]->get_type() == "archer") {
				heroes.emplace_back(std::make_unique<Archer>(cardPos.x, cardPos.y, "hero"));
			}
			previouslyPlacedCard = index;
			potion.decrease_potion_level(cards[index]->get_cost());
			cards[index]->return_to_position();
			remove_from_deck(index);
			card_shuffle(cards);
		}
	}
	
}

int Deck::get_selected_card(int index) {
	return selectedCards[index];
}

void Deck::update_timer(float& deltaTime) {
	if (timer < 5) {
		timer += deltaTime;
	}
}