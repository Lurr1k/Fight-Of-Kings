#include "Text.h"



Text::Text(std::string text, float size) : sign(font, text, size){
	textToDisplay = text;

	fontSize = size;

	font.openFromFile(FONTADDRESS);

	sign.setFont(font);
	sign.setString(textToDisplay);
	sign.setFillColor(sf::Color::Black);
}

void Text::update_text(std::string text) {
	sign.setString(text);

}
void Text::set_position(sf::Vector2f coordinates) {
	textPos = coordinates;
	sf::Vector2f bounds = sign.getLocalBounds().size;
	sign.setOrigin({ bounds.x / 2, bounds.y / 2 });
	sign.setPosition(textPos);
}


void Text::display_text(sf::RenderWindow& window) {
	window.draw(sign);
}

void Text::set_colour(sf::Color colour) {
	sign.setFillColor(colour);
}