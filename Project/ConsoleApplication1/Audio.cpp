#include "Audio.h"

Audio::Audio() {
	buffer.loadFromFile("res/blipSelect.wav");
	sound.setBuffer(buffer);
}

Audio* Audio::GetInstance() {
	if (!instance)
		instance = new Audio();
	return instance;
}

void Audio::Play() {
	sound.play();
}

Audio* Audio::instance = nullptr;
