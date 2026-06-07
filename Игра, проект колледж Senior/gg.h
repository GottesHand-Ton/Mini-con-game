#include <iostream>
#ifndef GG_H
#define GG_H
using namespace std;

class gg {
private:
	int hp;
	int maxhp;
	int damage;
	int x, y;
	
public:
	gg(int startx, int starty);


	void move(int dx, int dy) {
		x = dx;
		y = dy;
	}

	void takedamage(int atk) {
		hp -= atk;
		cout << "вы получили " << atk << " урона" << endl;
	}


	int gethp() const;
	int getdamage() const;
	int getx() const;
	int gety() const;
};




#endif
