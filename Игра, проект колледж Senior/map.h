#ifndef MAP_H
#define MAP_H
#include "gg.h"

class map {
private:
	static const int height = 9;
	static const int width = 9;
	char jey[height][width];


public:
	map();

	void paint(const gg& player, int numlocation);

	int getwidth() const { return width; }
	int getheight() const { return height; }
};




#endif