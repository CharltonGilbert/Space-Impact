#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
using namespace sf;


class Cbutton {
protected:
	Sprite button;
	Texture but;
public:
	Cbutton() {	}
	Sprite getbutton() {
		return button;
	}
};

class Cback : public Cbutton {
public:
	Cback() {
		but.loadFromFile("Graphics/back.png");
		button.setTexture(but);
		button.setPosition(5, 5);
		button.scale(0.2, 0.2);
	}
};
class Ctitle : public Cbutton {
public:
	Ctitle() {
		but.loadFromFile("Graphics/Header.png");
		button.setTexture(but);
		button.setPosition(45, 135);
		button.scale(0.25, 0.35);
	}
};

class Cstart : public Cbutton {
public:
	Cstart(){
		but.loadFromFile("Graphics/Start_BTN.png");
		button.setTexture(but);
		button.scale(0.3, 0.3);
		button.setPosition(100, 268);
	}
};

class Cexit : public Cbutton {
public:
	Cexit() {
		but.loadFromFile("Graphics/Exit_BTN.png");
		button.setTexture(but);
		button.scale(0.3, 0.3);
		button.setPosition(100, 338);
	}
};


#endif
