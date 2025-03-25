#include "Game.h"
#include "Character.h"
// Tasks:
// Range x
// Damage mechanics x
// Health bar x
// 

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

    enemies.emplace_back((std::make_unique<Tower>(187.5, 80)));
    enemies.emplace_back((std::make_unique<Tower>(562.5, 80)));
    enemies.emplace_back((std::make_unique<Tower>(375, 160)));
    heroes.emplace_back((std::make_unique<Goblin>(width/2, height/2)));
    heroes.emplace_back((std::make_unique<Giant>(width / 2 - 10, height / 2)));
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
    for (int i = 0; i < heroes.size(); i++) {
        heroes[i]->draw_character(window);

    }
    character.draw_character(window);
	window.display();

}


Game::Game() : character(1920, 1080) {
    init_window();
    instantiate_characters();
}

void Game::running() {
    while (window.isOpen()) {
        update_screen();
        for (int j = 0; j < heroes.size(); j++) {
            for (int i = 0; i < enemies.size(); i++) {
                if (heroes[j]->get_name() != "Tower") {
                    heroes[j]->move_towards_enemy(*enemies[0], enemies);
                    enemies[i]->move_towards_enemy(*heroes[0], heroes);
                }
                
            }
        }
        poll_events();
    }
}