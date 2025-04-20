#include "Potion.h"
#include <iostream>
#include "SFML/Graphics.hpp"


Potion::Potion() {
    potionBarBackground.setSize({ 40, 4 });
    potionBarBackground.setOrigin({ 20, 0 });
    potionBarBackground.setPosition({0,0});
    potionBarBackground.setFillColor(sf::Color(64,64,64));

}