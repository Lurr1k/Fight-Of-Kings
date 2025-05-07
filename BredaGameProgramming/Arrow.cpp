#include "Arrow.h"

Arrow::Arrow() {
    arrowTexture.loadFromFile("images/arrow.png");
    arrow.setTexture(arrowTexture, true);
    arrow.setPosition({ -100,-100 });
    sf::Vector2f arrowSize = arrow.getLocalBounds().size;
    arrow.setOrigin({ arrowSize.x / 2, arrowSize.y / 2 });
    velocity = 250;
}

bool Arrow::is_flying() {
    return arrowFlying;
}

void Arrow::move_arrow(sf::Vector2f target, float& deltaTime) {
    if (arrowFlying){
        sf::Vector2f distanceVector = targetPos - arrow.getPosition();
        float distance = sqrt(distanceVector.x * distanceVector.x + distanceVector.y * distanceVector.y);
        std::string moving;

        if (distance > 10) {
            if (distanceVector.x < -2) {
                moving = "left";
                arrow.move({ -velocity * deltaTime, 0.f });
                arrow.setRotation(sf::degrees(-90));
            }
            else if (distanceVector.x > 2) {
                moving = "right";
                arrow.move({ velocity * deltaTime, 0.f });
                arrow.setRotation(sf::degrees(90));
            }

            if (distanceVector.y < -2) {
                arrow.move({ 0, -velocity * deltaTime });
                if (moving == "left") {
                    arrow.setRotation(sf::degrees(-45));
                }
                else if (moving == "right") {
                    arrow.setRotation(sf::degrees(45));
                }
                else {
                    arrow.setRotation(sf::degrees(0));
                }
            }

            else if (distanceVector.y > 2) {
                arrow.move({ 0.f, velocity * deltaTime });
                if (moving == "left") {
                    arrow.setRotation(sf::degrees(-135));
                }
                else if (moving == "right") {
                    arrow.setRotation(sf::degrees(135));
                }
                else {
                    arrow.setRotation(sf::degrees(180));
                }
            }
        }
        else {
            arrow.setPosition(startPos);
            arrowFlying = false;
        }
    }
    
}

void Arrow::shoot(sf::Vector2f initial, sf::Vector2f target) {
    startPos = initial;
    targetPos = target;
    arrow.setPosition(startPos);
    arrowFlying = true;
    std::cout << targetPos.x;
}


void Arrow::draw_arrow(sf::RenderWindow& window) {
    window.draw(arrow);
}


