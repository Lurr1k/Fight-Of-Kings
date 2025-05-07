#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>


class Arrow {
private:
	sf::Texture arrowTexture;
	sf::Sprite arrow = sf::Sprite(arrowTexture);
	bool arrowFlying = false;
	sf::Vector2f startPos;
	sf::Vector2f targetPos;
	float velocity;
public:
	Arrow();
	bool is_flying();
	void move_arrow(sf::Vector2f target, float& deltaTime);
	void shoot(sf::Vector2f initial, sf::Vector2f target);
	void draw_arrow(sf::RenderWindow& window);
};