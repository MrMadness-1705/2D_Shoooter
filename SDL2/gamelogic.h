#pragma once
#include"bullet.h"
#include "enemy.h"
#include"ship.h"

class GameLogic {
public:
    bool checkCollision(Ship ship, Enemy& enemy) {
        int x1 = ship.getX();
        int y1 = ship.getY();
        int x2 = enemy.getX();
        int y2 = enemy.getY();
        if (x1 < x2 + 100 && x1 + 100 > x2 && y1 < y2 + 100 && y1 + 100 > y2) {
            return true;
        }
        else {
            return false;
        }
    }

    bool checkCollision(Bullet& bullet, Enemy& enemy) {
        int x1 = bullet.getX();
        int y1 = bullet.getY();
        int x2 = enemy.getX();
        int y2 = enemy.getY();
        if (x1 < x2 + 100 && x1 + 10 > x2 && y1 < y2 + 100 && y1 + 10 > y2) {
            return true;
        }
        else {
            return false;
        }
    }

    bool checkCollision(Bullet& bullet, Ship ship) {
        int x1 = bullet.getX();
        int y1 = bullet.getY();
        int x2 = ship.getX();
        int y2 = ship.getY();
        if (x1 < x2 + 100 && x1 + 10 > x2 && y1 < y2 + 100 && y1 + 10 > y2) {
            return true;
        }
        else {
            return false;
        }
    }
};