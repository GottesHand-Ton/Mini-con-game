#include <iostream>
#include "map.h"
#include "gg.h"
using namespace std;

map::map() {
	for (int i = 0; height > i; ++i) {
		for (int j = 0; width > j; ++j) {
			jey[i][j] = '.';
		}
	}
}

void map::paint(const gg& player) {
	for (int i = 0; height > i; ++i) {
		for (int j = 0; width > j; ++j) {
			jey[i][j] = '.';
		}
	}

	int ggx = player.getx();
	int ggy = player.gety();

	if (ggx >= 0 && ggx < width && ggy >= 0 && ggy < height) {
		jey[ggx][ggy] = 'A';
	}

	for (int i = 0; height > i; ++i) {
		for (int j = 0; width > j; ++j) {
			cout << jey[i][j] << " ";
		}
		cout << endl;
	}



}
