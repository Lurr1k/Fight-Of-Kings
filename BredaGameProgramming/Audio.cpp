#include "Audio.h"


void Audio::init_sounds() {
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
    pageBuffer.loadFromFile("sounds/page.mp3");
    pageSound.setBuffer(pageBuffer);
    pageSound.setVolume(40);
    initialised = true;
}

void Audio::toggle_sounds() {
    if (paused) {
        paused = false;
        if (initialised) {
            backgroundMusic.play();
        }
        
        std::cout << "Unpaused";
    }
    else {
        paused = true;
        if (initialised) {
            backgroundMusic.pause();
        }
        std::cout << "Paused";
    }
}

void Audio::play_slash() {
    if (not paused) {
        slashSound.play();
    }
}

void Audio::play_huh() {
    if (not paused) {
        huhSound.play();
    }
}

void Audio::play_page() {
    if (not paused) {
        pageSound.play();
    }
}

void Audio::character_sound(const std::string& soundPath) {
    std::cout << paused;
    if (not paused) {
        characterBuffer.loadFromFile(soundPath);
        characterSound.setBuffer(characterBuffer);
        characterSound.setVolume(40);
        characterSound.play();
        std::cout << paused;
    }
}