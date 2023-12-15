#pragma once

#include <iostream> //Console output

class Character{
    public:
        Character();
        Character(int x, int y, int w, int h, int hp, int dmg, int speed);
        ~Character();

        //Getters
        int getX();
        int getY();
        int getW();
        int getH();
        int getHP();
        int getDmg();
        int getSpeed();

        //Setters
        void setX(int x);
        void setY(int y);
        void setW(int w);
        void setH(int h);
        void setHP(int hp);
        void setDmg(int dmg);
        void setSpeed(int speed);

        //Other
        void move(int x, int y);
        void moveX(int x);
        void moveY(int y);
        void takeDamage(int dmg);
        void heal(int hp);
        bool isAlive();

    private:
        int x;
        int y;
        int w;
        int h;
        int hp;
        int dmg;
        int speed;
};