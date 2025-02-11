#include "Character.h"
#include "SFML/Graphics.hpp"
sf::CircleShape circle;

void Circle::go_up() {
    circle.move({ 0, -1 });
}

void Circle::go_down() {
    circle.move({ 0,10 });
}
void Circle::go_right() {
    circle.move({ 10,0 });
}
void Circle::go_left() {
    circle.move({ -10,0 });
}
void Circle::draw_circle(sf::RenderWindow& window) {
    window.draw(this->circle);
}