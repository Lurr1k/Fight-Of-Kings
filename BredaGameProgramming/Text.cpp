#include "Text.h"



Text::Text(std::string text, float size) : sign(font, text, size){
	textToDisplay = text;

	fontSize = size;

	font.openFromFile(FONTADDRESS);

	sign.setFont(font);
	sign.setString(textToDisplay);
	sign.setFillColor(sf::Color::Black);
}

// Updates the text of the text sign
void Text::update_text(std::string text) {
	sign.setString(text);

}

// Sets the text's position on the screen
void Text::set_position(sf::Vector2f coordinates) {
	textPos = coordinates;
	sf::Vector2f bounds = sign.getLocalBounds().size;
	sign.setOrigin({ bounds.x / 2, bounds.y / 2 });
	sign.setPosition(textPos);
}

// Displays the text on the screen
void Text::display_text(sf::RenderWindow& window) {
	window.draw(sign);
}
// Sets the text colour
void Text::set_colour(sf::Color colour) {
	sign.setFillColor(colour);
}