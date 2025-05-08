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
	// Returns whether the arrow is currently flying
	bool is_flying();
	// Moves the arrow towards the target
	void move_arrow(sf::Vector2f target, float& deltaTime);
	// Launches the arrow from the initial position
	void shoot(sf::Vector2f initial, sf::Vector2f target);
	// Displays the arrow
	void draw_arrow(sf::RenderWindow& window);
};