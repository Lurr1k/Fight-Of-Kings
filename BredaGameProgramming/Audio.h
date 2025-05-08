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

public:

	// Plays the slash sound
	void play_slash();


	// Plays the huh sound
	void play_huh();

	// Plays the page sound
	void play_page();

	//
	void toggle_sounds();

	void init_sounds();

	void character_sound(const std::string& soundPath);
};
