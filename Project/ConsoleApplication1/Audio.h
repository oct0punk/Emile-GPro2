#pragma once
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"

class Audio {

private:
	sf::SoundBuffer stdShotBuf;
	sf::SoundBuffer themBuf;
	sf::SoundBuffer slowBuf;
	sf::SoundBuffer lHitBuf;
	float pitch = 1.0f;

	Audio();	
	static Audio* instance;


public:
	sf::Sound stdShot;
	sf::Sound them;
	sf::Sound slow;
	sf::Sound lHit;

	static Audio* GetInstance();

	void Play(sf::Sound* s);

	void SetPitch(float val) {
		pitch = val;
		stdShot.setPitch(val);
		them.setPitch(val);
		slow.setPitch(val);
		lHit.setPitch(val);
	}
};

