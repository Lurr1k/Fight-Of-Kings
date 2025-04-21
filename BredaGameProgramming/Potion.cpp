#include "Potion.h"
#include <iostream>
#include "SFML/Graphics.hpp"


Potion::Potion() {
    potionBarBackground.setSize({ 40, 4 });
    potionBarBackground.setOrigin({ 0, 0 });
    potionBarBackground.setPosition({0,0});
    potionBarBackground.setFillColor(sf::Color(64,64,64));
    potionLevelBar.setSize({ 0,0 });
    potionLevelBar.setFillColor(sf::Color::Magenta);
    potionLevelBar.setPosition({ 0,0 });
    potionLevel = 0;
}

void Potion::display_potion(sf::RenderWindow &window) {
    window.draw(potionBarBackground);
    window.draw(potionLevelBar);
}