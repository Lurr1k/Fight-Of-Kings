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
    levelCircle.setOrigin(levelCircle.getGeometricCenter());
    levelCircle.setFillColor(sf::Color::Yellow);
    levelCircle.setRadius(30);
    levelCircle.setPosition({ 670, 10 });
    levelSign.set_position(695, 30);

}

void Potion::display_potion(sf::RenderWindow &window) {
    levelSign.update_text(std::to_string(static_cast<int>(std::floor(potionLevel))));
    window.draw(potionBarBackground);
    window.draw(potionLevelBar);
    window.draw(levelCircle);
    levelSign.display_text(window);
}

void Potion::increase_potion_level(float &deltaTime) {
    float time = deltaTime;
    if (potionLevel < 10) {
        potionLevel += 0.357 * time;
    }
    else if (potionLevel > 10) {
        potionLevel = 10;
    }
    std::cout << potionLevel;
    std::cout << "\n";
    potionLevelBar.setSize({potionLevel * 75,10 });
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