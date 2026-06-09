#ifndef GG_H
#define GG_H

class gg {
private:
    int hp;
    int maxhp;
    int damage;
    int x, y;
    int location;

public:
    gg(int startx, int starty);

    void move(int dx, int dy);
    void takedamage(int atk);
    void golocation();
    void exitlocanion();

    int gethp() const;
    int getdamage() const;
    int getx() const;
    int gety() const;
    int getlocation() const;
};

#endif