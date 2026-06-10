#include "gg.h"
#include <iostream>

using namespace std;

gg::gg(int startx, int starty) {
    maxhp = 100;
    hp = maxhp;
    base_damage = 1;
    damage = base_damage;
    x = startx;
    y = starty;
    location = 1;
    equippedWeaponIdx = -1;
}

void gg::move(int dx, int dy) {
    x += dx;
    y += dy;
}

void gg::takedamage(int atk) {
    hp -= atk;
    if (hp < 0) hp = 0;
    cout << "Вы получили " << atk << " урона! Осталось HP: " << hp << "%" << endl;
}

void gg::heal(int amount) {
    hp += amount;
    if (hp > maxhp) hp = maxhp;
    cout << "Вы восстановили " << amount << " HP. Текущее HP: " << hp << "%" << endl;
}

void gg::golocation() {
    location += 1;
    x = 1;
    y = 1;
}

void gg::exitlocanion() {
    location -= 1;
    x = 7;
    y = 7;
}

void gg::setPosition(int nx, int ny) {
    x = nx;
    y = ny;
}

int gg::gethp() const { return hp; }
int gg::getdamage() const { return damage; }
int gg::getx() const { return x; }
int gg::gety() const { return y; }
int gg::getlocation() const { return location; }

void gg::addItem(Item item) {
    inventory.push_back(item);
    cout << "В инвентарь добавлено: " << item.name << endl;
}

void gg::showInventory() {
    if (inventory.empty()) {
        cout << "Инвентарь пуст." << endl;
        return;
    }
    cout << "=== ИНВЕНТАРЬ ===" << endl;
    for (size_t i = 0; i < inventory.size(); ++i) {
        cout << i + 1 << ". " << inventory[i].name;
        if (inventory[i].isWeapon) {
            cout << " (Оружие, Урон: +" << inventory[i].value << ")";
            if ((int)i == equippedWeaponIdx) cout << " [ЭКИПИРОВАНО]";
        }
        else {
            cout << " (Зелье, Лечение: " << inventory[i].value << ")";
        }
        cout << endl;
    }
    cout << "0. Выйти из инвентаря" << endl;
}

void gg::useItem(int choice) {
    int idx = choice - 1;
    if (idx < 0 || idx >= (int)inventory.size()) return;

    if (inventory[idx].isWeapon) {
        if (equippedWeaponIdx == idx) {
            equippedWeaponIdx = -1;
            damage = base_damage;
            cout << "Вы сняли " << inventory[idx].name << endl;
        }
        else {
            equippedWeaponIdx = idx;
            damage = base_damage + inventory[idx].value;
            cout << "Вы экипировали " << inventory[idx].name << ". Текущий урон: " << damage << endl;
        }
    }
    else {
        heal(inventory[idx].value);
        inventory.erase(inventory.begin() + idx);
        if (equippedWeaponIdx > idx) equippedWeaponIdx--;
        else if (equippedWeaponIdx == idx) equippedWeaponIdx = -1;
    }
}