#include "Cards.h"
#include "SFML/Graphics.hpp"
#include <iostream>


Card::Card(const std::string& TEXTUREPATH, std::string type, float cost) : card(texture){

    cardType = type;
    cardCost = cost;

    texture.loadFromFile(TEXTUREPATH);

    card.setTexture(texture, true);
    

    sf::Vector2f boundCoordinates = card.getLocalBounds().size;

    card.setOrigin({ boundCoordinates.x / 2, boundCoordinates.y / 2 });

};

void Card::set_initial_position(float xPosition, float yPosition) {
    initialX = xPosition;
    initialY = yPosition;
    card.setPosition({ xPosition, yPosition });
}

void Card::card_dragging(sf::RenderWindow& window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    card.setPosition({ static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y) });
     card.getGlobalBounds().size;
}

void Card::draw_card(sf::RenderWindow& window) {
    window.draw(card);
}

bool Card::mouse_on_card(sf::RenderWindow &window) {
    bool cardIsHovered = false;
    sf::FloatRect bounds = card.getGlobalBounds();
    sf::Vector2i intCoords = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosition = { static_cast<float>(intCoords.x), static_cast<float>(intCoords.y) };
    if (bounds.contains(mousePosition)) {
        cardIsHovered = true;
    }

    return cardIsHovered;
}

void Card::select_card() {
    selected = true;
}

bool Card::is_selected() {
    return selected;
}

void Card::deselect_card() {
    selected = false;
}

void Card::return_to_position() {
    card.setPosition({ initialX, initialY });
}

sf::Vector2f Card::get_position() {
    return card.getPosition();
}

std::string Card::get_type() {

    return cardType;
}

void Card::set_card_position(float xPosition, float yPosition) {
    card.setPosition({ xPosition, yPosition });
}

float Card::get_cost() {
    return cardCost;
}