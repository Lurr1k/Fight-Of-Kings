#include "Game.h"

// Initialises the window and sets the window resolution
void Game::init_window(){
	height = 960;
	width = 750;
	windowTitle = "The Fight of Kings";
	resolution = sf::VideoMode({ width, height });
	window = sf::RenderWindow(resolution, windowTitle, sf::Style::Close);
    window.setPosition({ 585, 20 });
    window.setVerticalSyncEnabled(true);
}

// Loads the backgrounds for all of the screens
void Game::load_background() {
    backgroundTexture.loadFromFile("images/backgroundTexture.png");
    helpPageTexture.loadFromFile("images/HelpPage1.png");
    helpPage2Texture.loadFromFile("images/HelpPage2.png");
    startPageTexture.loadFromFile("images/StartPage.png");
    endPageTexture.loadFromFile("images/EndPage.png");
    background.emplace(backgroundTexture);
    helpPageBackground.emplace(helpPageTexture);
    helpPage2Background.emplace(helpPage2Texture);
    startPageBackground.emplace(startPageTexture);
    endPageBackground.emplace(endPageTexture);
}

//Instantiates the towers and cards for the game.
void Game::instantiate_characters() {
    cards.push_back(std::make_unique<GoblinCard>());
    cards.push_back(std::make_unique<GiantCard>());
    cards.push_back(std::make_unique<ArcherCard>());
    cards.push_back(std::make_unique<GoblinCard>());
    cards.push_back(std::make_unique<GoblinCard>());
    cards.push_back(std::make_unique<GoblinCard>());
    enemies.push_back(std::make_unique<Tower>(187.5, 280, "enemy"));
    enemies.push_back(std::make_unique<Tower>(562.5, 280, "enemy"));
    enemies.push_back(std::make_unique<Tower>(375, 200, "enemy"));
    heroes.push_back(std::make_unique<Tower>(187.5, 680, "hero"));
    heroes.push_back(std::make_unique<Tower>(562.5, 680, "hero"));
    heroes.push_back(std::make_unique<Tower>(375, 760, "hero"));
}

//Scans for events and performs their consequences
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
            if (keyPressed->button == sf::Mouse::Button::Left) {
                if (gameRunning) {
                    for (int i = 0; i < 5; i++) {
                        cardIndex = decky.get_selected_card(i);
                        if (cards[cardIndex]->mouse_on_card(window) and cardIndex != -1) {
                            cards[cardIndex]->select_card();
                        }
                    }
                }
                else if (helpScreen.back_hovered(window) and (helpPage or helpPage2)) {
                    helpPage = false;
                    helpPage2 = false;
                    startPage = true;
                    bookSound.play();
                }
                else if (helpScreen.next_hovered(window) and (helpPage or helpPage2)) {
                    if (helpPage) {
                        helpPage = false;
                        helpPage2 = true;
                    }
                    else if (helpPage2) {
                        helpPage = true;
                        helpPage2 = false;
                    }
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
                if (gameRunning) {
                    for (int i = 0; i < 5; i++) {
                        cardIndex = decky.get_selected_card(i);
                       
                        if (cards[cardIndex]->mouse_on_card(window) and cardIndex != -1) {
                            cards[cardIndex]->deselect_card();
                            decky.spawn_or_return(cards, heroes, potion, cardIndex);
                        }
                    }
                }
                
            }
        }
    }
}

// Updates the screen
void Game::update_screen() {
    window.clear();
    if (gameRunning) {
        window.draw(*background);
        for (auto& enemy:enemies) {
            enemy->display_health_bar(window);
            enemy->draw_character(window);

        }
        for (auto& hero : heroes) {
            hero->display_health_bar(window);
            hero->draw_character(window);

        }
        decky.display_deck(window, cards);
        potion.display_potion(window);
    }
    else if (helpPage or helpPage2) {
        if (helpPage) {
            window.draw(*helpPageBackground);
        }
        else {
            window.draw(*helpPage2Background);
        }
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

// Game constructor, initialises the window, the sounds and loads the backgrounds
Game::Game() {
    init_window();
    init_sounds();
    load_background();
}

// Performed each time the game starts, resets everything on the game screen and switches to the game screen
void Game::start_game() {
    instantiate_characters();
    gameRunning = true;
    startPage = false;
    potion.decrease_potion_level(10);
    distribution.reset_potion();
    slashSound.play();
}

// The general game loop
void Game::running() {
    int cardIndex;
    while (window.isOpen()) {
        update_screen();
        poll_events();
        if (gameRunning) {
            float deltaTime = clock.restart().asSeconds();
            decky.card_shuffle(cards);
            decky.update_timer(deltaTime);
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
            for (auto& hero:heroes) {
                if ((heroes.size() > 0) and (enemies.size() > 0)) {
                    hero->move_and_attack(enemies, deltaTime);
                } 
            }
            for (auto& enemy:enemies) {
                if ((heroes.size() > 0) and (enemies.size() > 0)) {
                    enemy->move_and_attack(heroes, deltaTime);
                }
            }
            check_if_game_over();
        }

    }
}

// Checks if any of the sides has lost all three towers, and if that is the case, finishes the game and switches to the end screen.
void Game::check_if_game_over() {
    int heroesTowerCount = 0;
    int enemiesTowerCount = 0;
    for (auto& hero : heroes) {
        if (hero->get_name() == "Tower") {
            heroesTowerCount += 1;
        }
    }
    for (auto& enemy : enemies) {
        if (enemy->get_name() == "Tower") {
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

// Initialises sounds 
void Game::init_sounds() {
    backgroundMusic.openFromFile("sounds/shrimp quartet.mp3");
    backgroundMusic.setLooping(true);
    backgroundMusic.play();
    backgroundMusic.setVolume(3);
    slashBuffer.loadFromFile("sounds/slash.mp3");
    slashSound.setBuffer(slashBuffer);
    slashSound.setVolume(3);
    huhBuffer.loadFromFile("sounds/huh.mp3");
    huhSound.setBuffer(huhBuffer);
    huhSound.setVolume(10);
    bookBuffer.loadFromFile("sounds/book.mp3");
    bookSound.setBuffer(bookBuffer);
    bookSound.setVolume(40);
}

// Mutes the music
void Game::mute_music() {
    if (backgroundMusic.getStatus() == sf::SoundSource::Status::Playing) {
        backgroundMusic.pause();
    }
    else {
        backgroundMusic.play();
    }
}