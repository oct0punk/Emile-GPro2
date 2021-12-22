#include "Audio.h"
#include "Game.h"

Audio::Audio() {
	stdShotBuf.loadFromFile("res/blipSelect.wav");
	stdShot.setBuffer(stdShotBuf);
	themBuf.loadFromFile("res/them.wav");
	them.setBuffer(themBuf); 
	them.setVolume(0.5f);
	them.setPlayingOffset(sf::seconds(68.4f));
	them.play();
	lHitBuf.loadFromFile("res/laserHit.wav");
	lHit.setBuffer(lHitBuf);
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
	s->setPitch(pitch);
	s->play();
}

Audio* Audio::instance = nullptr;
