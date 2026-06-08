#include <iostream>
#include <windows.h>
#include <clocale>
#include <string>
#include "gg.h"
#include "map.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
    gg newgg(4, 4);
    map mymap{};

	char movechoice = ' ';
	cout << "Управление:\nQ - Выход \n \nW - Вверх \nS - Вниз  \nA - Влево  \nD - право \n \nH - Посмотреть характеристики \nI - Открыть инвентарь" << endl;

	while (movechoice != 'q' && movechoice != 'Q') {
		mymap.paint(newgg, newgg.getlocation());

		if (newgg.getx() == mymap.getwidth() - 1 && newgg.gety() == mymap.getheight() - 1) {
			newgg.golocation();
		}
		else if (newgg.getx() == 0 && newgg.gety() == 0) {
			newgg.exitlocanion();
		}

		else {
			cout << "Действуй!" << endl;
			cin >> movechoice;

			if ((movechoice == 'a' || movechoice == 'A') && newgg.gety() > 0) {
				newgg.move(0, -1);
			}
			else if ((movechoice == 'd' || movechoice == 'D') && newgg.gety() < 8) {
				newgg.move(0, 1);
			}
			else if ((movechoice == 'w' || movechoice == 'W') && newgg.getx() > 0) {
				newgg.move(-1, 0);
			}
			else if ((movechoice == 's' || movechoice == 'S') && newgg.getx() < 8) {
				newgg.move(1, 0);
			}
			else {

			}
		}
	}
	return 0;

}



