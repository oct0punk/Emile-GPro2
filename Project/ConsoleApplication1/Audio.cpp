#include "Audio.h"
#include "Game.h"

Audio::Audio() {
	stdShotBuf.loadFromFile("res/blipSelect.wav");
	stdShot.setBuffer(stdShotBuf);
	stdShot.setVolume(50);

	themBuf.loadFromFile("res/them.wav");
	them.setBuffer(themBuf); 
	them.setVolume(10);
	them.setPlayingOffset(sf::seconds(68.4f));
	them.play();

	lHitBuf.loadFromFile("res/laserHit.wav");
	lHit.setBuffer(lHitBuf);
	lHit.setVolume(40);
	
	slowBuf.loadFromFile("res/slow.wav");
	slow.setBuffer(slowBuf);
	
	pitch = Game::GetInstance()->world->timeScale;
}

Audio* Audio::GetInstance() {
	if (!instance)
		instance = new Audio();
	return instance;
}

void Audio::Play(sf::Sound* s) {
	float p = (rand() % 3000) / 10000.0f;
	s->setPitch(pitch + p);
	s->play();
}

Audio* Audio::instance = nullptr;
