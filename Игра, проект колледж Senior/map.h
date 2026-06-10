#ifndef MAP_H
#define MAP_H

#include "gg.h"
#include <string>

class map {
private:
    static const int height = 9;
    static const int width = 9;
    char jey[height][width];

    bool locOpened[6];
    bool chestOpened[6]; 
    bool npcInteracted[6];

public:
    map();

    void loadLocation(int numlocation);
    void paint(const gg& player);

    void clearCell(int x, int y);
    bool isLocationOpened(int num) const { return locOpened[num]; }
    void openLocation(int num) { locOpened[num] = true; }

    bool isChestOpened(int num) const { return chestOpened[num]; }
    void openChest(int num) { chestOpened[num] = true; }

    bool isNpcDone(int num) const { return npcInteracted[num]; }
    void setNpcDone(int num) { npcInteracted[num] = true; }

    char getCell(int x, int y) const { return jey[x][y]; }
    int getwidth() const { return width; }
    int getheight() const { return height; }

    void setLocStatus(int num, bool status) { locOpened[num] = status; }
    void setChestStatus(int num, bool status) { chestOpened[num] = status; }
    void setNpcStatus(int num, bool status) { npcInteracted[num] = status; }
};

#endif