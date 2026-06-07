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
    map Mymap{};

	char movechoiceanta = ' ';
	cout << "Управление:\nQ - Выход \n \nW - Вверх \nS - Вниз  \nA - Влево  \nD - право \n \nH - Посмотреть характеристики \nI - Открыть инвентарь" << endl;

	while (movechoiceanta != 'q' && movechoiceanta != 'Q') {
		Mymap.paint(newgg, newgg.getlocation());
		cout << "Действуй!" << endl;
		cin >> movechoiceanta;

		if ((movechoiceanta == 'a' || movechoiceanta == 'A') && newgg.gety() > 0) {
			newgg.move(0, -1);
		}
		else if ((movechoiceanta == 'd' || movechoiceanta == 'D') && newgg.gety() < 8) {
			newgg.move(0, 1);
		}
		else if ((movechoiceanta == 'w' || movechoiceanta == 'W') && newgg.getx() > 0) {
			newgg.move(-1, 0);
		}
		else if ((movechoiceanta == 's' || movechoiceanta == 'S') && newgg.getx() < 8) {
			newgg.move(1, 0);
		}
		else {

		}
	}
	return 0;

}



