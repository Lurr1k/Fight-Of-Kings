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

// Toggles the sounds
void Audio::toggle_sounds() {
    if (paused) {
        paused = false;
       
        backgroundMusic.play();
        
    }
    else {
        paused = true;
      
        backgroundMusic.pause();
        
    }
}

// Plays the slash sound
void Audio::play_slash() {
    if (not paused) {
        slashSound.play();
    }
}

// Plays the huh sound
void Audio::play_huh() {
    if (not paused) {
        huhSound.play();
    }
}

// Plays the page sound
void Audio::play_page() {
    if (not paused) {
        pageSound.play();
    }
}

// Plays the sound corresponding to the spawned character
void Audio::character_sound(const std::string& soundPath) {
    if (not paused) {
        characterBuffer.loadFromFile(soundPath);
        characterSound.setBuffer(characterBuffer);
        characterSound.setVolume(40);
        characterSound.play();
    }
}