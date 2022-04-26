#ifndef SOUNDS_H
#define SOUNDS_H
#include <SFML/Audio.hpp>
using namespace sf;

class Csound {
protected:
	SoundBuffer buffer;
	Sound fx;
public:
	Csound(){}
	void plays() {
		fx.play();
	}
};

class Csong :public Csound {
public:
	Csong() {
		buffer.loadFromFile("Sounds/spaceinvaders1.wav");
		fx.setBuffer(buffer);
		fx.setVolume(30);
	}
};

class Claser : public Csound {
public:
	Claser() {
		buffer.loadFromFile("Sounds/shoot.wav");
		fx.setBuffer(buffer);
		fx.setVolume(30);
	}
};

#endif
