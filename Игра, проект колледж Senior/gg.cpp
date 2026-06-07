#include "gg.h"
#include <iostream>
using namespace std;

gg::gg(int startx, int starty) {
	 maxhp = 10;
	 hp = maxhp;
	 damage = 1;
	 x = startx;
	 y = starty;
	 location = 1;
}

void gg::move(int dx, int dy) {
	x += dx;
	y += dy;
}

void gg::takedamage(int atk) {
	hp -= atk;
	cout << "вы получили " << atk << " урона" << endl;
}

void gg::golocation() {
	location += 1;
}


void gg::exitlocanion() {
	location -= 1;
}


int gg::gethp() const { return hp; }
int gg::getdamage() const { return damage; }
int gg::getx() const { return x; }
int gg::gety() const { return y; }
int gg::getlocation() const { return location; };

