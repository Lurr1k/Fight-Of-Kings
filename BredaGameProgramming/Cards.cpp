#include "Cards.h"
#include "SFML/Graphics.hpp"
#include <iostream>


Card::Card(const std::string& TEXTUREPATH, float xPosition, float yPosition) : card(texture){
    texture.loadFromFile(TEXTUREPATH);

    card.setTexture(texture, true);

    sf::Vector2f bounds = card.getLocalBounds().size;

    card.setOrigin({ bounds.x / 2, bounds.y / 2 });

    card.setPosition({ xPosition, yPosition });

};

void Card::card_dragging(sf::RenderWindow& window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    card.setPosition({ static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y) });
}

void Card::draw_card(sf::RenderWindow& window) {
    window.draw(card);
}