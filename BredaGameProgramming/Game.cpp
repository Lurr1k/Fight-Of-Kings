#include "Game.h"
#include "Character.h"
#include "Cards.h"
#include "Deck.h"
#include "Potion.h"
#include "Distribution.h"
#include "Screens.h"


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
    helpPageTexture.loadFromFile("images/HelpPage.png");
    startPageTexture.loadFromFile("images/StartPage.png");
    background.emplace(backgroundTexture);
    helpPageBackground.emplace(helpPageTexture);
    startPageBackground.emplace(startPageTexture);
}

void Game::instantiate_characters() {
    cards.emplace_back(std::make_unique<GoblinCard>());
    cards.emplace_back(std::make_unique<GiantCard>());
    cards.emplace_back(std::make_unique<GoblinCard>());
    cards.emplace_back(std::make_unique<GoblinCard>());
    cards.emplace_back(std::make_unique<GoblinCard>());
    cards.emplace_back(std::make_unique<GoblinCard>());
    enemies.emplace_back(std::make_unique<Tower>(187.5, 280, "enemy"));
    enemies.emplace_back(std::make_unique<Tower>(562.5, 280, "enemy"));
    enemies.emplace_back(std::make_unique<Tower>(375, 200, "enemy"));
    heroes.emplace_back(std::make_unique<Tower>(187.5, 680, "hero"));
    heroes.emplace_back(std::make_unique<Tower>(562.5, 680, "hero"));
    heroes.emplace_back(std::make_unique<Tower>(375, 760, "hero"));
}

void Game::poll_events() {
    int cardIndex;
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
            std::cout << "Mouse";
            if (keyPressed->button == sf::Mouse::Button::Left) {
                std::cout << "Left";
                if (gameRunning) {
                    for (int i = 0; i < 5; i++) {
                        std::cout << i;
                        cardIndex = decky.get_selected_card(i);
                        if (cards[cardIndex]->mouse_on_card(window) and cardIndex != -1) {
                            std::cout << "selected";
                            cards[cardIndex]->select_card();
                        }
                    }
                }
                else if (helpScreen.back_hovered(window)) {
                    helpPage = false;
                }
                else if (startingScreen.start_hovered(window) and not (helpPage or gameRunning)) {
                    gameRunning = true;
                    clock.restart();
                }
                else if (startingScreen.help_hovered(window) and not (helpPage or gameRunning)) {
                    helpPage = true;
                    std::cout << "shmobs";
                }

            }
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonReleased>()) {
            if (keyPressed->button == sf::Mouse::Button::Left) {
                std::cout << "Left";
                if (gameRunning) {
                    for (int i = 0; i < 5; i++) {
                        cardIndex = decky.get_selected_card(i);
                        std::cout << i;
                        if (cards[cardIndex]->mouse_on_card(window) and cardIndex != -1) {
                            std::cout << "deselected";
                            cards[cardIndex]->deselect_card();
                            decky.spawn_or_return(cards, heroes, potion);
                        }
                    }
                }
                
            }
        }
    }
}


void Game::update_screen() {
    window.clear();
    if (gameRunning) {
        window.draw(*background);
        for (int i = 0; i < enemies.size(); i++) {
            enemies[i]->display_health_bar(window);
            enemies[i]->draw_character(window);

        }
        for (int i = 0; i < heroes.size(); i++) {
            heroes[i]->display_health_bar(window);
            heroes[i]->draw_character(window);

        }
        decky.display_deck(window, cards);
        potion.display_potion(window);
    }
    else if (helpPage) {
        window.draw(*helpPageBackground);
        helpScreen.draw_help_screen(window);
        helpScreen.scan_hovered(window);
    }
    else {
        window.draw(*startPageBackground);
        startingScreen.draw_starting_screen(window);
        startingScreen.scan_hovered(window);
    }
	window.display();

}


Game::Game() {
    init_window();
    load_background();
    instantiate_characters();
}

void Game::start_game() {
    instantiate_characters();
    gameRunning = true;
}

void Game::running() {
    int cardIndex;
    while (window.isOpen()) {
        update_screen();
        if (gameRunning) {
            float deltaTime = clock.restart().asSeconds();
            decky.card_shuffle(cards);
            potion.increase_potion_level(deltaTime);
            distribution.spawn_enemies(deltaTime, heroes, enemies);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            
                for (int i = 0; i < 5; i++) {
                    cardIndex = decky.get_selected_card(i);
                    if (cards[cardIndex]->is_selected()) {
                        cards[cardIndex]->card_dragging(window);
                    }
                
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
        }
        poll_events();
    }
}
