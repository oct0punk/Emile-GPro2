#pragma once
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"

struct AudioClip {
	sf::Sound s;
	sf::SoundBuffer buf;
	float volume = 1.0f;
	float pitch = 1.0f;
};

class Audio {

private:
	sf::SoundBuffer stdShotBuf;
	sf::SoundBuffer themBuf;
	sf::SoundBuffer slowBuf;
	sf::SoundBuffer lHitBuf;
	sf::SoundBuffer hitBuf;
	sf::SoundBuffer powerBuf;
	float pitch = 1.0f;

	Audio();	
	static Audio* instance;


public:
	float* generalVol = new float(1.0f);
	sf::Sound stdShot;
	sf::Sound them;
	sf::Sound slow;
	sf::Sound lHit;
	sf::Sound hit;
	sf::Sound power;

	static Audio* GetInstance();

	void Play(sf::Sound* s);

	void SetPitch(float val) {
		pitch = val;
		stdShot.setPitch(val);
		them.setPitch(val);
		lHit.setPitch(val);
		power.setPitch(val);
		hit.setPitch(val);
	}

	void GlobalVolumeSet() {

	}
};

