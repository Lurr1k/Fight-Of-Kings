#include "Text.h"
#include <iostream>
#include "SFML/Graphics.hpp"


Text::Text(std::string text, float size) : sign(font, text, 20){
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
void Text::set_position(float xPosition, float yPosition) {
	textPosition = { xPosition, yPosition };
	sf::Vector2f bounds = sign.getLocalBounds().size;
	sign.setOrigin({ bounds.x / 2, bounds.y / 2 });
	sign.setPosition(textPosition);
}


void Text::display_text(sf::RenderWindow &window) {
	window.draw(sign);
}