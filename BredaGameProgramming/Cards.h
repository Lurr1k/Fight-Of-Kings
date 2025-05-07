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

	void set_initial_position(float xPos, float yPos);

	void card_dragging(sf::RenderWindow& window);

	void draw_card(sf::RenderWindow& window);
	
	bool mouse_on_card(sf::RenderWindow& window);

	void select_card();

	bool is_selected();

	void deselect_card();

	void return_to_position();
	
	sf::Vector2f get_position();
	
	std::string get_type();

	void set_card_position(float xPos, float yPos);

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
class ArcherCard : public Card {
public:
	ArcherCard() : Card("images/ArcherCard.png", "archer", 3) {}
};