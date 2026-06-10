#ifndef GG_H
#define GG_H

#include <string>
#include <vector>

struct Item {
    int id;
    std::string name;
    int value;
    bool isWeapon;
};

class gg {
private:
    int hp;
    int maxhp;
    int damage;
    int base_damage;
    int x, y;
    int location;
    std::vector<Item> inventory;
    int equippedWeaponIdx;

public:
    gg(int startx, int starty);

    void move(int dx, int dy);
    void takedamage(int atk);
    void heal(int amount);
    void golocation();
    void exitlocanion();
    void setPosition(int nx, int ny);

    int gethp() const;
    int getdamage() const;
    int getx() const;
    int gety() const;
    int getlocation() const;

    void addItem(Item item);
    void showInventory();
    void useItem(int choice);
    const std::vector<Item>& getInventory() const { return inventory; }
    void clearInventory() { inventory.clear(); }
    int getEquippedIdx() const { return equippedWeaponIdx; }
    void forceEquip(int idx) { equippedWeaponIdx = idx; }
};

#endif