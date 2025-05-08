#pragma once
#include <iostream>
#include <SFML/Audio.hpp>


class Audio {
private:
	bool initialised = false;
	bool paused = false;
	sf::Music backgroundMusic;
	sf::SoundBuffer slashBuffer;
	sf::Sound slashSound = sf::Sound(slashBuffer);
	sf::SoundBuffer huhBuffer;
	sf::Sound huhSound = sf::Sound(huhBuffer);
	sf::SoundBuffer pageBuffer;
	sf::Sound pageSound = sf::Sound(pageBuffer);
	sf::SoundBuffer characterBuffer;
	sf::Sound characterSound = sf::Sound(characterBuffer);
	sf::SoundBuffer endBuffer;
	sf::Sound endSound = sf::Sound(endBuffer);


public:
	// Makes the audio a singleton class
	static Audio& instance() {
		static Audio instance;
		return instance;
	}

	// Plays the slash sound
	void play_slash();


	// Plays the huh sound
	void play_huh();

	// Plays the page sound
	void play_page();

	// Toggles the sounds 
	void toggle_sounds();

	// Initialises the background and page sounds
	void init_sounds();

	// Plays the sound corresponding to the spawned character
	void character_sound(const std::string& soundPath);

	// Plays the sound once the game is over
	void end_sound(const std::string& soundPath);
};
