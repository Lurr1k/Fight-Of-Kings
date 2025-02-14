#include "Game.h"
#include "Character.h"



void Game::init_window(){
	height = 960;
	width = 750;
    frameLimit = 60;
	windowTitle = "The Fight of Kings";
	resolution = sf::VideoMode({ width, height });
	window = sf::RenderWindow(resolution, windowTitle);
    window.setFramerateLimit(frameLimit);
}

void Game::instantiate_characters() {
    bob = Circle(700, 940);
    character.set_position(width / 2, height / 2);
}

void Game::poll_events() {
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {

            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                window.close();
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::W) {
                bob.go_up();
            }
        }

    }
}


void Game::update_screen() {
    window.clear();
    bob.draw_circle(window);
    character.draw_character(window);
	window.display();

}


Game::Game() : character("images/LookingUp.png") {
    init_window();
    instantiate_characters();
}

void Game::running() {
    while (window.isOpen()) {
        update_screen();
        sf::Vector2f position = bob.get_position();
        character.move_towards_enemy(position);
        poll_events();
    }
}