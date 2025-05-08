#include "Cards.h"



Card::Card(const std::string& texturePath, const std::string& type, float cost){

    cardType = type;
    cardCost = cost;

    texture.loadFromFile(texturePath);

    card.setTexture(texture, true);
    

    sf::Vector2f boundCoordinates = card.getLocalBounds().size;

    card.setOrigin({ boundCoordinates.x / 2, boundCoordinates.y / 2 });

};
// Sets the initial position of the card in the current deck (used to return it when incorrectly placed)
void Card::set_initial_position(float xPosition, float yPosition) {
   initialX = xPosition;
   initialY = yPosition;
    card.setPosition({ xPosition, yPosition });
}
// Moves the card after the mouse cursor
void Card::card_dragging(sf::RenderWindow& window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    card.setPosition({ static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y) });
}

// Displays the card
void Card::draw_card(sf::RenderWindow& window) {
    window.draw(card);
}

// Detects is the mouse is hovered over the card
bool Card::mouse_on_card(sf::RenderWindow& window) {
    bool cardIsHovered = false;
    sf::FloatRect bounds = card.getGlobalBounds();
    sf::Vector2i intCoords = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosition = { static_cast<float>(intCoords.x), static_cast<float>(intCoords.y) };
    if (bounds.contains(mousePosition)) {
        cardIsHovered = true;
    }

    return cardIsHovered;
}

// Marks the card as selected
void Card::select_card() {
    selected = true;
}

// Returns whether the card is selected
bool Card::is_selected() {
    return selected;
}

// Marks the card as unselected
void Card::deselect_card() {
    selected = false;
}

// Returns the card to its position in the deck
void Card::return_to_position() {
    card.setPosition({ initialX, initialY });
}

// Returns the card's position
sf::Vector2f Card::get_position() {
    return card.getPosition();
}

// Returns the card's character type
std::string Card::get_type() {

    return cardType;
}

// Places the card at the set coordinates
void Card::set_card_position(float xPosition, float yPosition) {
    card.setPosition({ xPosition, yPosition });
}

// Returns the cost of the card
float Card::get_cost() {
    return cardCost;
}