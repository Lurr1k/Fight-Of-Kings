#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Card {
private: 
	float initialX;
	float initialY;
	sf::Texture texture;
	sf::Sprite card = sf::Sprite(texture);
	bool selected = false;
	std::string cardType;
	float cardCost;

public:

	Card(const std::string& TEXTUREPATH, const std::string& type, float cost);

	// Sets the initial position of the card in the current deck (used to return it when incorrectly placed)
	void set_initial_position(float xPos, float yPos);

	// Moves the card after the mouse cursor 
	void card_dragging(sf::RenderWindow& window);

	// Displays the card
	void draw_card(sf::RenderWindow& window);
	
	// Detects is the mouse is hovered over the card
	bool mouse_on_card(sf::RenderWindow& window);

	// Marks the card as selected
	void select_card();

	// Returns whether the card is selected
	bool is_selected();

	// Marks the card as unselected
	void deselect_card();

	// Returns the card to its position in the deck
	void return_to_position();
	
	// Returns the card's position
	sf::Vector2f get_position();
	
	// Returns the card's character type
	std::string get_type();

	// Places the card at the set coordinates
	void set_card_position(float xPos, float yPos);

	// Returns the cost of the card
	float get_cost();

};

// Goblin card 
class GoblinCard : public Card {
public:
	GoblinCard() : Card("images/GoblinCard.png", "goblin", 2) {}
};
// Giant card
class GiantCard : public Card {
public:
	GiantCard() : Card("images/GiantCard.png", "giant", 5) {}
};
// Archer card
class ArcherCard : public Card {
public:
	ArcherCard() : Card("images/ArcherCard.png", "archer", 3) {}
};