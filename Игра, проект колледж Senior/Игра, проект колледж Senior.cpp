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
        mymap.paint(newgg);

        cout << "Действуй!" << endl;
        cin >> movechoice;

        int nextX = newgg.getx();
        int nextY = newgg.gety();
        int dx = 0;
        int dy = 0;
        bool wantToMove = false;

        if (movechoice == 'a' || movechoice == 'A') {
            nextY = newgg.gety() - 1;
            dy = -1;
            wantToMove = true;
        }
        else if (movechoice == 'd' || movechoice == 'D') {
            nextY = newgg.gety() + 1;
            dy = 1;
            wantToMove = true;
        }
        else if (movechoice == 'w' || movechoice == 'W') {
            nextX = newgg.getx() - 1;
            dx = -1;
            wantToMove = true;
        }
        else if (movechoice == 's' || movechoice == 'S') {
            nextX = newgg.getx() + 1;
            dx = 1;
            wantToMove = true;
        }

        if (wantToMove) {
            if (nextX >= 0 && nextX < mymap.getheight() && nextY >= 0 && nextY < mymap.getwidth()) {
                char targetCell = mymap.getCell(nextX, nextY);

                if (targetCell != '#') {
                    if (targetCell == 'D') {
                        if (nextX == 7 && nextY == 8) {
                            newgg.golocation();
                            mymap.loadLocation(newgg.getlocation());
                        }
                        else if (nextX == 1 && nextY == 0) {
                            newgg.exitlocanion();
                            mymap.loadLocation(newgg.getlocation());
                        }
                    }
                    else {
                        newgg.move(dx, dy);
                    }

                    system("cls");
                }
            }
        }
    }
    return 0;
}