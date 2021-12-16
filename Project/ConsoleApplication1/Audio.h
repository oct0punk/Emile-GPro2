#pragma once
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"

class Audio {
	sf::Sound sound;
	sf::SoundBuffer buffer;

private:
	Audio() {
		buffer.loadFromFile("res/blipSelect.wav");
		sound.setBuffer(buffer);
	}

	static Audio* instance;


public:

	static Audio* GetInstance() {
		if (!instance)
			instance = new Audio();
		return instance;
	}

	void Play() {
		sound.play();
	}

};

Audio* Audio::instance = nullptr;
