#include "Game.h"
#include "Character.h"



void Game::init_window(){
	height = 960;
	width = 750;
	windowTitle = "The Fight of Kings";
	resolution = sf::VideoMode({ width, height });
	window = sf::RenderWindow(resolution, windowTitle);
}

void Game::instantiate_characters() {
    circle = Circle(width / 2, height / 2);
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
                circle.go_up();
            }
        }

    }
}


void Game::update_screen() {
	window.clear();
    circle.draw_circle(window);
	window.display();

}


Game::Game() {
    init_window();
    instantiate_characters();
}

void Game::running() {
    while (window.isOpen()) {
        update_screen();

        poll_events();
    }
}