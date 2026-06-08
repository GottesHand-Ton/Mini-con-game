#include <iostream>
#include <windows.h>      
#include <clocale>
#include <string>
#include "gg.h"
#include "map.h"

using namespace std;


map::map() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	for (int i = 0; height > i; ++i) {
		for (int j = 0; width > j; ++j) {
			jey[i][j] = '.';
		}
	}
}


void map::paint(const gg& player, int numlocation) {

	int ggx = player.getx();
	int ggy = player.gety();

	if (numlocation == 1) {
		cout << "Вы переходите в ущелье точек" << endl;
		for (int i = 0; height > i; ++i) {
			for (int j = 0; width > j; ++j) {
				jey[i][j] = '.';
			}
		}

		if (ggx >= 0 && ggx < width && ggy >= 0 && ggy < height) {
			jey[ggx][ggy] = 'A';
		}


		jey[height - 1][width - 1] = '+';

		for (int i = 0; height > i; ++i) {
			for (int j = 0; width > j; ++j) {
				cout << jey[i][j] << " ";
			}
			cout << endl;
		}

	}
	else if (numlocation == 2) {
		cout << "Вы переходите в лавовую долину решёток" << endl;
		
		for (int i = 0; height > i; ++i) {
			for (int j = 0; width > j; ++j) {
				jey[i][j] = '#';
			}
		}

		jey[height - 1][width - 1] = '+';
		jey[0][0] = '-';

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
	else if (numlocation == 3) {
		cout << "Вы переходите в смешшную землю" << endl;
		for (int i = 0; height > i; ++i) {
			for (int j = 0; width > j; ++j) {
				jey[i][j] = ')';
			}
		}

		jey[height - 1][width - 1] = '+';
		jey[0][0] = '-';

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
	else if (numlocation == 4) {
		cout << "Вы переходите в грустную землю" << endl;
		for (int i = 0; height > i; ++i) {
			for (int j = 0; width > j; ++j) {
				jey[i][j] = '(';
			}
		}

		jey[height - 1][width - 1] = '+';
		jey[0][0] = '-';

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
	else if (numlocation == 5) {
		cout << "Вы переходите в ромашковое поле" << endl;
		for (int i = 0; height > i; ++i) {
			for (int j = 0; width > j; ++j) {
				jey[i][j] = '?';
			}
		}
		jey[height - 1][width - 1] = '+';
		jey[0][0] = '-';
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





}
