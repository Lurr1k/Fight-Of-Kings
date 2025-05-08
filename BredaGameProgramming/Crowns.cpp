#include "Crowns.h"


Crown::Crown() {

	texturePath = "images/Crown.png";

	texture.loadFromFile(texturePath);

	crown.setTexture(texture, true);

	crown.setPosition({ -100,-100 });

}

// Displays the crown
void Crown::display_crown(sf::RenderWindow& window) {
	window.draw(crown);
}

// Sets the crown's position at the given coordinates
void Crown::set_position(sf::Vector2f coordinates) {
	crown.setPosition(coordinates);
}