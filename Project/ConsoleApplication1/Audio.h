#pragma once
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"

class Audio {
	sf::Sound stdShot;
	sf::SoundBuffer stdShotBuf;
	sf::Sound them;
	sf::SoundBuffer themBuf;
	float* pitch = nullptr;

private:
	Audio();
	
	static Audio* instance;


public:

	static Audio* GetInstance();

	void Play();

};

