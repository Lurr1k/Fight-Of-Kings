#include "Potion.h"
#include <iostream>
#include "SFML/Graphics.hpp"


Potion::Potion() {
    potionBarBackground.setSize({ 750, 20 });
    potionBarBackground.setOrigin({ 0, 0 });
    potionBarBackground.setPosition({0,0});
    potionBarBackground.setFillColor(sf::Color(64,64,64));
    potionLevelBar.setSize({ 0,0 });
    potionLevelBar.setFillColor(sf::Color::Yellow);
    potionLevelBar.setPosition({ 0,0 });
    potionLevel = 0;
}

void Potion::display_potion(sf::RenderWindow &window) {
    window.draw(potionBarBackground);
    window.draw(potionLevelBar);
}

void Potion::increase_potion_level(float &deltaTime) {
    float time = deltaTime;
    if (potionLevel < 10) {
        potionLevel += 0.125 * time;
    }
    else if (potionLevel > 10) {
        potionLevel = 10;
    }
    std::cout << potionLevel;
    std::cout << "\n";
    potionLevelBar.setSize({potionLevel*75,10 });
}

void Potion::decrease_potion_level(float amount) {
    potionLevel -= amount;
    if (potionLevel < 0) {
        potionLevel = 0;
    }
}

float Potion::get_potion_level() {
    return potionLevel;
}