#include <iostream>
#include <fstream>
#include <windows.h>
#include <clocale>
#include <string>
#include <vector>
#include <cstdlib>
#include "gg.h"
#include "map.h"

using namespace std;

void logEvent(const string& message) {
    ofstream logFile("log.txt", ios::app);
    if (logFile.is_open()) {
        logFile << "[LOG]: " << message << endl;
        logFile.close();
    }
}

void saveGame(const gg& player, const map& mymap) {
    ofstream saveFile("save.txt");
    if (saveFile.is_open()) {
        saveFile << player.getlocation() << " " << player.getx() << " " << player.gety() << " " << player.gethp() << " " << player.getdamage() << endl;
        for (int i = 1; i <= 5; i++) {
            saveFile << mymap.isLocationOpened(i) << " " << mymap.isChestOpened(i) << " " << mymap.isNpcDone(i) << endl;
        }
        saveFile << player.getInventory().size() << endl;
        for (const auto& item : player.getInventory()) {
            saveFile << item.id << " " << item.value << " " << item.isWeapon << " " << item.name << endl;
        }
        saveFile << player.getEquippedIdx() << endl;
        saveFile.close();
        cout << "Игра успешно сохранена!" << endl;
        logEvent("Игра сохранена.");
    }
}


bool loadGame(gg& player, map& mymap) {
    ifstream saveFile("save.txt");
    if (!saveFile.is_open()) return false;

    int loc, x, y, hp, dmg;
    if (!(saveFile >> loc >> x >> y >> hp >> dmg)) return false;

    player.setPosition(x, y);
    player.heal(hp - player.gethp());

    for (int i = 1; i <= 5; i++) {
        bool lo, co, no;
        saveFile >> lo >> co >> no;
        mymap.setLocStatus(i, lo);
        mymap.setChestStatus(i, co);
        mymap.setNpcStatus(i, no);
    }

    size_t invSize;
    saveFile >> invSize;
    player.clearInventory();
    for (size_t i = 0; i < invSize; i++) {
        Item item;
        saveFile >> item.id >> item.value >> item.isWeapon;
        saveFile.ignore();
        getline(saveFile, item.name);
        player.addItem(item);
    }
    int eqIdx;
    saveFile >> eqIdx;
    player.forceEquip(eqIdx);

    mymap.loadLocation(loc);
    while (player.getlocation() < loc) {
        player.golocation();
    }
    player.setPosition(x, y);

    saveFile.close();
    logEvent("Игра загружена из сохранения.");
    return true;
}

void startCombat(gg& player, string enemyName, int enemyHp, int enemyAtk) {
    system("cls");
    cout << "=== НАЧАЛСЯ БОЙ С " << enemyName << " ===" << endl;
    logEvent("Игрок вступил в бой с " + enemyName);

    while (player.gethp() > 0 && enemyHp > 0) {
        cout << "\nВаше HP: " << player.gethp() << "% | HP Врага: " << enemyHp << endl;
        cout << "1. Напасть\n2. Открыть инвентарь (выпить зелье)\n3. Сбежать" << endl;
        int action;
        cin >> action;

        if (action == 1) {
            enemyHp -= player.getdamage();
            cout << "Вы нанесли " << player.getdamage() << " урона." << endl;
            if (enemyHp <= 0) break;
        }
        else if (action == 2) {
            player.showInventory();
            cout << "Выберите номер зелья (или 0 для возврата): ";
            int choice;
            cin >> choice;
            if (choice > 0) player.useItem(choice);
            continue;
        }
        else {
            cout << "Вы трусливо сбежали!" << endl;
            logEvent("Игрок сбежал из боя.");
            return;
        }

        player.takedamage(enemyAtk);
    }

    if (player.gethp() <= 0) {
        cout << "Вы погибли в бою... Игра окончена." << endl;
        logEvent("Игрок погиб.");
        exit(0);
    }
    else {
        cout << "Победа! Враг повержен." << endl;
        logEvent("Игрок победил в бою.");
    }
}

void interactNPC(gg& player, map& mymap) {
    system("cls");
    cout << "=== Разговор со Странником ===" << endl;
    cout << "Странник: Приветствую тебя, искатель приключений. Зачем ты здесь?" << endl;
    cout << "1. Я ищу выход из этого проклятого места.\n2. Отдавай свои шмотки или пожалеешь! (Напасть)" << endl;

    int c;
    cin >> c;
    if (c == 2) {
        startCombat(player, "Странник", 40, 10);
        Item masterSword = { 2, "Меч Мастера", 15, true };
        player.addItem(masterSword);
        mymap.setNpcDone(player.getlocation());
        mymap.clearCell(player.getx(), player.gety());
    }
    else {
        cout << "\nСтранник: Хм, я могу помочь тебе оружием, если ответишь на мой вопрос: Что не имеет длины, ширины, но его можно измерить?" << endl;
        cout << "1. Время\n2. Тень\n3. Смерть" << endl;
        cin >> c;
        if (c == 1) {
            cout << "\nСтранник: Верно! Держи этот клинок." << endl;
            Item ironSword = { 1, "Железный нож", 5, true };
            player.addItem(ironSword);
        }
        else {
            cout << "\nСтранник: Неверно. Я ухожу от тебя." << endl;
        }
        mymap.setNpcDone(player.getlocation());
        mymap.clearCell(player.getx(), player.gety());
    }
}

bool runPuzzle(int locIndex) {
    system("cls");
    cout << "=== Впереди закрытые врата! Разгадайте замок локации " << locIndex << " ===" << endl;
    if (locIndex == 2) {
        cout << "Математический шифр. Решите уравнение: 7 * 8 - (12 + 4) = ?" << endl;
        int ans; cin >> ans;
        return ans == 40;
    }
    else if (locIndex == 3) {
        cout << "Загадка: Кто ходит утром на четырех ногах, днем на двух, а вечером на трех?" << endl;
        cout << "1. Обезьяна\n2. Человек\n3. Собака" << endl;
        int ans; cin >> ans;
        return ans == 2;
    }
    else if (locIndex == 4) {
        cout << "Шифр слов. Какое слово зашифровано: 'ОДРГО'?" << endl;
        cout << "1. ГОРОД\n2. ДОРОГ\n3. ДОНОР" << endl;
        int ans; cin >> ans;
        return ans == 1;
    }
    else if (locIndex == 5) {
        cout << "Тест на интуицию. Какое число загадал компьютер от 1 до 3?" << endl;
        int ans; cin >> ans;
        return ans == 2;
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "Russian");
    gg newgg(4, 4);
    map mymap{};

    logEvent("Игра запущена.");

    cout << "Найти сохранение? (1 - Да, 0 - Новая игра): ";
    int loadChoice;
    cin >> loadChoice;
    if (loadChoice == 1) {
        if (!loadGame(newgg, mymap)) {
            cout << "Файл сохранения не найден. Начинаем новую игру." << endl;
        }
    }

    char movechoice = ' ';

    while (movechoice != 'q' && movechoice != 'Q') {
        system("cls");
        mymap.paint(newgg);

        cout << "\n[ Локация: " << newgg.getlocation() << " | HP: " << newgg.gethp() << "% | Урон: " << newgg.getdamage() << " ]" << endl;
        cout << "Управление: W, A, S, D | I - Инвентарь | P - Сохранить | Q - Выйти" << endl;
        cout << "Действуй: ";
        cin >> movechoice;

        if (movechoice == 'i' || movechoice == 'I') {
            system("cls");
            newgg.showInventory();
            cout << "Выберите предмет: ";
            int choice;
            cin >> choice;
            newgg.useItem(choice);
            system("pause");
            continue;
        }

        if (movechoice == 'p' || movechoice == 'P') {
            saveGame(newgg, mymap);
            system("pause");
            continue;
        }

        int nextX = newgg.getx();
        int nextY = newgg.gety();
        int dx = 0, dy = 0;
        bool wantToMove = false;

        if (movechoice == 'a' || movechoice == 'A') { nextY--; dy = -1; wantToMove = true; }
        else if (movechoice == 'd' || movechoice == 'D') { nextY++; dy = 1; wantToMove = true; }
        else if (movechoice == 'w' || movechoice == 'W') { nextX--; dx = -1; wantToMove = true; }
        else if (movechoice == 's' || movechoice == 'S') { nextX++; dx = 1; wantToMove = true; }

        if (wantToMove) {
            if (nextX >= 0 && nextX < mymap.getheight() && nextY >= 0 && nextY < mymap.getwidth()) {
                char targetCell = mymap.getCell(nextX, nextY);

                if (targetCell != '#') {
                    if (targetCell == 'D') {
                        if (nextX == 7 && nextY == 8) {
                            int nextLocIdx = newgg.getlocation() + 1;

                            if (nextLocIdx == 6) {
                                system("cls");
                                cout << "=============================" << endl;
                                cout << "ПОБЕДА! ВЫ ВЫБРАЛИСЬ ИЗ ЛАБИРИНТА!" << endl;
                                cout << "=============================" << endl;
                                logEvent("Игрок успешно прошел игру (Победа).");
                                break;
                            }

                            if (!mymap.isLocationOpened(nextLocIdx)) {
                                if (runPuzzle(nextLocIdx)) {
                                    cout << "Головоломка решена! Локация открыта." << endl;
                                    mymap.openLocation(nextLocIdx);
                                    logEvent("Решена головоломка локации " + to_string(nextLocIdx));
                                    system("pause");
                                }
                                else {
                                    cout << "Ошибка! Замок бьет вас током." << endl;
                                    newgg.takedamage(25);
                                    logEvent("Игрок ошибся в головоломке. Получено 25 урона.");
                                    system("pause");
                                    if (newgg.gethp() <= 0) {
                                        cout << "Вы погибли... Конец игры." << endl;
                                        break;
                                    }
                                    continue;
                                }
                            }
                            newgg.golocation();
                            mymap.loadLocation(newgg.getlocation());
                        }

                        else if (nextX == 1 && nextY == 0) {
                            newgg.exitlocanion();
                            mymap.loadLocation(newgg.getlocation());
                        }
                    }
                    else if (targetCell == 'C') {
                        cout << "Вы нашли сундук!" << endl;
                        Item smallHeal = { 10, "Малое зелье лечения (+20 HP)", 20, false };
                        Item bigHeal = { 11, "Большое зелье лечения (+50 HP)", 50, false };
                        newgg.addItem(smallHeal);
                        newgg.addItem(bigHeal);
                        mymap.openChest(newgg.getlocation());
                        mymap.clearCell(nextX, nextY);
                        logEvent("Открыт сундук на локации " + to_string(newgg.getlocation()));
                        system("pause");
                    }
                    else if (targetCell == 'N') {
                        interactNPC(newgg, mymap);
                        system("pause");
                    }
                    else {
                        newgg.move(dx, dy);
                    }
                }
            }
        }
    }
    return 0;
}