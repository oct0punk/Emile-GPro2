#include "Audio.h"
#include "Game.h"

Audio::Audio() {
	buffer.loadFromFile("res/blipSelect.wav");
	sound.setBuffer(buffer);
	pitch = &Game::GetInstance()->world->timeScale;
}

Audio* Audio::GetInstance() {
	if (!instance)
		instance = new Audio();
	return instance;
}

void Audio::Play() {
	sound.setPitch(*pitch);
	sound.play();
}

Audio* Audio::instance = nullptr;
