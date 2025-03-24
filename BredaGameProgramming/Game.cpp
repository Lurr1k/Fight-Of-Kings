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
    enemies.emplace_back((std::make_unique<Goblin>(700,400)));
    enemies.emplace_back((std::make_unique<Giant>(400, 200)));
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
        }

    }
}


void Game::update_screen() {
    window.clear();
    
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i]->draw_character(window);
        
    }

    character.draw_character(window);
	window.display();

}


Game::Game() : character(500, 750) {
    init_window();
    instantiate_characters();
}

void Game::running() {
    while (window.isOpen()) {
        update_screen();
        for (int i = 0; i < enemies.size(); i++) {
            character.move_towards_enemy(*enemies[0], enemies);
        }
        
        poll_events();
    }
}