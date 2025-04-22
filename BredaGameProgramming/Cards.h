#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Card {
private: 
	float initialX;
	float initialY;
	sf::Texture texture;
	sf::Sprite card;
	bool selected = false;
	std::string cardType;
	float cardCost;

public:

	Card(const std::string& TEXTUREPATH, std::string type, float cost);

	void set_initial_position(float xPosition, float yPosition);

	void card_dragging(sf::RenderWindow& window);

	void draw_card(sf::RenderWindow& window);
	
	bool mouse_on_card(sf::RenderWindow& window);

	void select_card();

	bool is_selected();

	void deselect_card();

	void return_to_position();
	
	sf::Vector2f get_position();
	
	std::string get_type();

	void set_card_position(float xPosition, float yPosition);

	float get_cost();

};


class GoblinCard : public Card {
public:
	GoblinCard() : Card("images/GoblinCard.png", "goblin", 2) {}
};
class GiantCard : public Card {
public:
	GiantCard() : Card("images/GiantCard.png", "giant", 5) {}
};