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
    endPageTexture.loadFromFile("images/EndPage.png");
    background.emplace(backgroundTexture);
    helpPageBackground.emplace(helpPageTexture);
    startPageBackground.emplace(startPageTexture);
    endPageBackground.emplace(endPageTexture);
}

void Game::instantiate_characters() {
    cards.emplace_back(std::make_unique<GoblinCard>());
    cards.emplace_back(std::make_unique<GiantCard>());
    cards.emplace_back(std::make_unique<ArcherCard>());
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
                else if (helpScreen.back_hovered(window) and helpPage) {
                    helpPage = false;
                    startPage = true;
                    bookSound.play();
                }
                else if (startingScreen.start_hovered(window) and startPage) {
                    clock.restart();
                    start_game();
                }
                else if (startingScreen.help_hovered(window) and startPage) {
                    startPage = false;
                    helpPage = true;
                    huhSound.play();
                }
                else if (muteButton.detect_button_hovered(window) and startPage) {
                    mute_music();
                }
                else if (endScreen.return_hovered(window) and endPage) {
                    endPage = false;
                    startPage = true;
                    bookSound.play();
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
    else if (endPage) {
        window.draw(*endPageBackground);
        endScreen.draw_end_screen(window);
        endScreen.scan_hovered(window);
    }
    else if (startPage) {
        window.draw(*startPageBackground);
        muteButton.display_button(window);
        startingScreen.draw_starting_screen(window);
        startingScreen.scan_hovered(window);
        muteButton.scan_hovered(window);
    }
	window.display();

}


Game::Game() {
    init_window();
    init_sounds();
    load_background();
}

void Game::start_game() {
    instantiate_characters();
    gameRunning = true;
    startPage = false;
    potion.decrease_potion_level(10);
    distribution.reset_potion();
    slashSound.play();
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
            check_if_game_over();
        }
        poll_events();
    }
}

void Game::check_if_game_over() {
    int heroesTowerCount = 0;
    int enemiesTowerCount = 0;
    for (int i = 0; i < heroes.size(); i++) {
        if (heroes[i]->get_name() == "Tower") {
            heroesTowerCount += 1;
        }
    }
    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i]->get_name() == "Tower") {
            enemiesTowerCount += 1;
        }
    }
    if ((heroesTowerCount <= 0) or (enemiesTowerCount <= 0)) {
        gameRunning = false;
        endPage = true;
        endScreen.crown_creation((3 - enemiesTowerCount), (3 - heroesTowerCount));
        endScreen.set_result_text();
        enemies.clear();
        heroes.clear();
    }
}


void Game::init_sounds() {
    backgroundMusic.openFromFile("sounds/shrimp quartet.mp3");
    backgroundMusic.setLooping(true);
    backgroundMusic.play();
    backgroundMusic.setVolume(3);
    slashBuffer.loadFromFile("sounds/slash.mp3");
    slashSound.setBuffer(slashBuffer);
    slashSound.setVolume(10);
    huhBuffer.loadFromFile("sounds/huh.mp3");
    huhSound.setBuffer(huhBuffer);
    huhSound.setVolume(10);
    bookBuffer.loadFromFile("sounds/book.mp3");
    bookSound.setBuffer(bookBuffer);
    bookSound.setVolume(40);
}

void Game::mute_music() {
    backgroundMusic.pause();
}