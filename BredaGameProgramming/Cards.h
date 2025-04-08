#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Card {
private: 

	sf::Texture texture;
	sf::Sprite card;

public:

	Card(const std::string& TEXTUREPATH, float xCoordinate, float yCoordinate);

	void card_dragging(sf::RenderWindow& window);

	void draw_card(sf::RenderWindow& window);

	

};

class GoblinCard : public Card {
public:
	GoblinCard(float xCoordinate, float yCoordinate) : Card("images/GoblinCard.png", xCoordinate, yCoordinate) {}
};