#include "Game.h"
#include "Character.h"
#include "Cards.h"
#include "Deck.h"
// Tasks:
// Coordinates of deck angle: 150, 849; Size: 450, 111
// Create deck file and class
// The deck class should manage the card sorting and the deck float rect
// The sorting algorithm should control the pseudorandom distribution of cards
// Create elexir that gradually increases with time.
// Display it at the top
// If there is not enough elixir to spawn a card, then respawn the card

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
    cards.emplace_back(std::make_unique<GoblinCard>());
    cards.emplace_back(std::make_unique<GiantCard>());
    cards.emplace_back(std::make_unique<GoblinCard>());
    cards.emplace_back(std::make_unique<GoblinCard>());
    cards.emplace_back(std::make_unique<GoblinCard>());
    cards.emplace_back(std::make_unique<GoblinCard>());
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
                for (int i = 0; i < 5; i++) {
                    std::cout << i;
                    cardIndex = decky.get_selected_card(i);
                    if (cards[cardIndex]->mouse_on_card(window) and cardIndex != -1) {
                        std::cout << "selected";
                        cards[cardIndex]->select_card();
                    }
                }
            }
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::MouseButtonReleased>()) {
            if (keyPressed->button == sf::Mouse::Button::Left) {
                std::cout << "Left";
                for (int i = 0; i < 5; i++) {
                    cardIndex = decky.get_selected_card(i);
                    std::cout << i;
                    if (cards[cardIndex]->mouse_on_card(window) and cardIndex != -1) {
                        std::cout << "deselected";
                        cards[cardIndex]->deselect_card();
                        decky.spawn_or_return(cards, heroes);
                    }
                }
            }
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
    decky.display_deck(window, cards);
    character.draw_character(window);
	window.display();

}


Game::Game() : character(1920, 1080, ""){
    init_window();
    load_background();
    instantiate_characters();
}

void Game::running() {
    int cardIndex;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        decky.card_shuffle(cards);
        update_screen();
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
        
        poll_events();
    }
}
