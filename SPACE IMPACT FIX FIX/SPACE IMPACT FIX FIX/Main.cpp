#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <time.h>
#include "Button.h"
#include "Sounds.h"
using namespace sf;
using namespace std;

class Cobject {
protected:
	float _x, _y;
public:
	Cobject() {
		_x = _y = 0;
	}
	void set(float x, float y) {
		_x = x;_y = y;
	}
	float getx() {
		return _x;
	}
	float gety() {
		return _y;
	}
	virtual void setpos(float x, float y) {	}
	virtual void scale(float x, float y) {}
	virtual void move(float x, float y) {}
};

class Cbullet : public Cobject {
	Texture bul;
	Sprite bullet;
public:
	Cbullet() {}
	void addbullet() {
		bul.loadFromFile("Graphics/laserRed07.png");
		bullet.setTexture(bul);
	}
	void setpos(float x, float y) {
		bullet.setPosition(x, y);
		_x = x;_y = y;
	}
	void scale(float x, float y) {
		bullet.setScale(x, y);
	}
	void moves(float x, float y) {
		bullet.move(x, y);
		_x += x;
		_y += y;
	}
	Sprite getb() {
		return bullet;
	}
};

class Cplayer : public Cobject {
	Texture pla;
	Sprite player;

public:
	Cplayer() {
		pla.loadFromFile("Graphics/playerShip1_red.png");
		player.setTexture(pla);
	}
	void setpos(float x, float y) {
		player.setPosition(x, y);
		_x = x;_y = y;
	}
	void scale(float x, float y) {
		player.setScale(x, y);
	}
	void moves(float x, float y) {
		player.move(x, y);
		_x += x;
		_y += y;
	}
	Sprite getplayer() {
		return player;
	}
};

class Cenemy : public Cobject {
	Texture ene;
	Sprite enemy;
	int lastdir;
public:
	Cenemy() {
		ene.loadFromFile("Graphics/enemyRed1.png");
		enemy.setTexture(ene);
		lastdir = 0;
	}
	void addenemy() {
		enemy.setTexture(ene);
	}
	void setpos(float x, float y) {
		enemy.setPosition(x, y);
		_x = x;_y = y;
	}
	void scale(float x, float y) {
		enemy.setScale(x, y);
	}
	void moves(float x, float y) {
		enemy.move(x, y);
		_x += x;
		_y += y;
	}
	void setdir(int x) {
		lastdir = x;
	}
	void update() {
		double x;
		if (lastdir == 1) {
			if (_x ==270) {
				x = -0.5;
			}
			else if (_x ==0) {
				x = 0.5;
				setdir(2);
			}
			else {
				x = -0.5;
			}
			enemy.move(x, 0);
		}
		else if (lastdir == 2) {
			if (_x ==0) {
				x = 0.5;
			}
			else if (_x ==270 ) {
				x = -0.5;
				setdir(1);
			}
			else {
				x = 0.5;
			}
			enemy.move(x, 0);
		}
		_x += x;
	}
	Sprite getenemy() {
		return enemy;
	}
};

class Cworld {
	Sprite world;
	Texture wor;
public:
	Cworld() {
		wor.loadFromFile("Graphics/darkPurple.png");
		world.setTexture(wor);
		world.scale(2.5, 3);
	}
	Sprite getworld() {
		return world;
	}
};


class Cmainmenu {
	Sprite mainmenu;
	Texture main;
public:
	Cmainmenu() {
		main.loadFromFile("Graphics/main.jpg");
		mainmenu.setTexture(main);
		mainmenu.scale(0.1, 0.2);
		mainmenu.setPosition(-50, -50);
	}
	Sprite getmenu() {
		return mainmenu;
	}
};

class Cgame {
	double x, y;
	bool over = false;
	float dx, dy;
	int c = 0, start=0;
	vector <Cbullet*> bullet;
	Cplayer player;
	vector <Cenemy*>enemy;
	RenderWindow window;
	Cworld world;
	Cmainmenu mainmenu;
	Cbutton* startbtn, * exitbtn, * title, * back;
	Csound *song, *shoot;
	Event event;
	Clock clock;
	Time times;
public:
	void init() {
		startbtn = new Cstart;
		exitbtn = new Cexit;
		title = new Ctitle;
		back = new Cback;
		song = new Csong;
		shoot = new Claser;
		int rx, ry, r;
		srand(time(NULL));
		rx = rand() % 200 + 50;
		ry = rand() % 300 + 45;
		r = rand() % 2 + 1;
		enemy.push_back(new Cenemy);
		enemy[enemy.size() - 1]->scale(0.6, 0.6);
		enemy[enemy.size() - 1]->addenemy();
		enemy[enemy.size() - 1]->setpos(rx, ry);
		enemy[enemy.size() - 1]->setdir(r);

		rx = rand() % 200 + 50;
		ry = rand() % 300 + 45;
		r = rand() % 2 + 1;
		enemy.push_back(new Cenemy);
		enemy[enemy.size() - 1]->scale(0.6, 0.6);
		enemy[enemy.size() - 1]->addenemy();
		enemy[enemy.size() - 1]->setpos(rx, ry);
		enemy[enemy.size() - 1]->setdir(r);

		rx = rand() % 200 + 50;
		ry = rand() % 300 + 45;
		r = rand() % 2 + 1;
		enemy.push_back(new Cenemy);
		enemy[enemy.size() - 1]->scale(0.6, 0.6);
		enemy[enemy.size() - 1]->addenemy();
		enemy[enemy.size() - 1]->setpos(rx, ry);
		enemy[enemy.size() - 1]->setdir(r);

		player.setpos(125, 400);
		player.scale(0.7, 0.7);
		song->plays();
	}
	void run() {
		window.create(VideoMode(320, 480), "Space Impact");
		window.setPosition(sf::Vector2i(10, 50));

		// RUN
		while (over !=true) {
				while (window.pollEvent(event)) {
					if (event.type == Event::Closed) {
						window.close();
					}
				}
				if (start == 0) {
					window.draw(mainmenu.getmenu());
					menu();
				}
				if(start==1) {
					processinput();
					updates();
					draw();
				}
		}

	}
	void updates() {
		float x;
		int r;
		times = clock.getElapsedTime();
		x = times.asMilliseconds();
		x += 0.5;
		player.moves(dx*x, dy * x);
		for (int i = 0;i < 3;i++) {
			enemy[i]->update();
		}
		for (int i = 0;i < bullet.size();i++) {
			bullet[i]->moves(0 * x, -0.1 * x);
		}
		bulletcheck();
		for (int i = 0;i < 3;i++) {
			planecheck(i);
		}
		clock.restart();

	}
	void draw() {
		window.clear(Color::White);
		window.setFramerateLimit(120);
		window.draw(world.getworld());
		window.draw(player.getplayer());
		for (int i = 0;i < enemy.size();i++) {
			window.draw(enemy[i]->getenemy());
		}
		for (int i = 0;i < bullet.size();i++) {
			window.draw(bullet[i]->getb());
		}
		window.draw(back->getbutton());
		window.display();
	}
	void bulletcheck() {
		for (int q = 0;q < enemy.size();q++) {
			for (int j = 0;j < bullet.size();j++) {
				if (bullet[j]->getx() >= enemy[q]->getx() - 33 && bullet[j]->getx()  <= enemy[q]->getx() + 33) {
					if (bullet[j]->gety() + 5 < enemy[q]->gety() + 50 ) {
						delbullet(j);
					}
				}
			}
		}
	}
	void planecheck(int q) {
		if (player.getx() + 33 >= enemy[q]->getx() - 13 && player.getx() + 33 <= enemy[q]->getx() + 33) {
			if (player.gety() - 15 <= enemy[q]->gety() + 40) {
				//delplane
			}
		}
	}
	void delbullet(int ind) {
		bullet.erase(bullet.begin() + ind);
	}
	void menu() {
		window.draw(title->getbutton());
		window.draw(startbtn->getbutton());
		window.draw(exitbtn->getbutton());
		window.display();
		if (event.mouseMove.x < 215 && event.mouseMove.x > 110) {
			if (event.mouseMove.y < 296 && event.mouseMove.y > 273) {
				if (Mouse::isButtonPressed(Mouse::Left)) {
					start = 1;
					shoot->plays();
				}
			}
		}
		if (event.mouseMove.x < 215 && event.mouseMove.x > 110) {
			if (event.mouseMove.y < 361 && event.mouseMove.y > 338) {
				if (Mouse::isButtonPressed(Mouse::Left)) {
					over = true;
					shoot->plays();
				}
			}
		}
	}
	void processinput() {
		if (add() && c>10) {
			bullet.push_back(new Cbullet);
			bullet[bullet.size() - 1]->scale(0.5,0.5);
			bullet[bullet.size() - 1]->addbullet();
			bullet[bullet.size() - 1]->setpos(player.getx() + 33,player.gety()-15);
			c = 0;
			shoot->plays();
		}
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			dy = -0.1;
			c++;
		}
		else if (Keyboard::isKeyPressed(Keyboard::A)) {
			dx = -0.1;
			c++;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S)) {
			dy = 0.1;
			c++;
		}
		else if (Keyboard::isKeyPressed(Keyboard::D)) {
			dx = 0.1;
			c++;
		}
		else
			dx = dy = 0;
	}
	bool add() {
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			return true;
		}
		else
			return false;
	}
};
int main() {
	Cgame game;
	game.init();
	game.run();
	
}

