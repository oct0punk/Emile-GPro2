#include "Audio.h"
#include "Game.h"

Audio::Audio() {
	stdShotBuf.loadFromFile("res/blipSelect.wav");
	stdShot.setBuffer(stdShotBuf);
	pitch = &Game::GetInstance()->world->timeScale;
	themBuf.loadFromFile("res/them.wav");
	them.setBuffer(themBuf);
	
	them.setPlayingOffset(sf::seconds(68.4f));
	them.play();
}

Audio* Audio::GetInstance() {
	if (!instance)
		instance = new Audio();
	return instance;
}

void Audio::Play() {
	stdShot.setPitch(*pitch);
	stdShot.play();
}

Audio* Audio::instance = nullptr;
