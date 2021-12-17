#pragma once
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"

class Audio {
	sf::Sound sound;
	sf::SoundBuffer buffer;

private:
	Audio();
	
	static Audio* instance;


public:

	static Audio* GetInstance();

	void Play();

};

