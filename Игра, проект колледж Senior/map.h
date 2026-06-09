#ifndef MAP_H
#define MAP_H

#include "gg.h" // Теперь подключаем напрямую, чтобы paint знал структуру класса

class map {
private:
    static const int height = 9;
    static const int width = 9;
    char jey[height][width];

public:
    map();

    void loadLocation(int numlocation);
    void paint(const gg& player);

    char getCell(int x, int y) const { return jey[x][y]; }
    int getwidth() const { return width; }
    int getheight() const { return height; }
};

#endif