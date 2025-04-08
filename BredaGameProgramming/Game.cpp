#include "Game.h"
#include "Character.h"
#include "Cards.h"
// Tasks:
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

void Game::load_background() {
    backgroundTexture.loadFromFile("images/backgroundTexture.png");
    background.emplace(backgroundTexture); 
}

void Game::instantiate_characters() {
    cards.emplace_back(std::make_unique<GoblinCard>(213, 904.5));
    enemies.emplace_back(std::make_unique<Tower>(187.5, 280, "enemy"));
    enemies.emplace_back(std::make_unique<Tower>(562.5, 280, "enemy"));
    enemies.emplace_back(std::make_unique<Tower>(375, 200, "enemy"));
    enemies.emplace_back(std::make_unique<Goblin>(750, 960, "enemy"));
    heroes.emplace_back(std::make_unique<Tower>(187.5, 680, "hero"));
    heroes.emplace_back(std::make_unique<Tower>(562.5, 680, "hero"));
    heroes.emplace_back(std::make_unique<Tower>(375, 760, "hero"));
    heroes.emplace_back(std::make_unique<Goblin>(width / 2, height / 2, "hero"));
    heroes.emplace_back(std::make_unique<Giant>(750, 0, "hero"));
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
        else if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            std::cout << "shmobus";
        }
    }
}


void Game::update_screen() {
    window.clear();
    window.draw(*background);
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i]->display_health_bar(window);
        enemies[i]->draw_character(window);
        
    }
    for (int i = 0; i < heroes.size(); i++) {
        heroes[i]->display_health_bar(window);
        heroes[i]->draw_character(window);

    }
    for (int i = 0; i < cards.size(); i++) {
        cards[i]->draw_card(window);
    }
    character.draw_character(window);
	window.display();

}


Game::Game() : character(1920, 1080, "aaa") {
    init_window();
    load_background();
    instantiate_characters();
}

void Game::running() {
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        update_screen();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            for (int i = 0; i < cards.size(); i++) {
                cards[i]->card_dragging(window);
            }
        }
        for (int j = 0; j < heroes.size(); j++) {
            if ((heroes.size() > 0) && (enemies.size() > 0)) {
                heroes[j]->move_towards_enemy(enemies, deltaTime);
            } 
        }
        for (int i = 0; i < enemies.size(); i++) {
            if ((heroes.size() > 0) && (enemies.size() > 0)) {
                enemies[i]->move_towards_enemy(heroes, deltaTime);
            }
        }
        poll_events();
    }
}
