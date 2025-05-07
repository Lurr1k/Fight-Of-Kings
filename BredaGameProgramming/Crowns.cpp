#include "Crowns.h"


Crown::Crown() {

	texturePath = "images/Crown.png";

	texture.loadFromFile(texturePath);

	crown.setTexture(texture, true);

}

void Crown::display_crown(sf::RenderWindow& window) {
	window.draw(crown);
}

void Crown::set_position(sf::Vector2f coordinates) {
	crown.setPosition(coordinates);
}