#pragma once
#include<SDL.h>

// Bullet class definition
class Bullet {
private:
    int x;  // x-coordinate of the bullet
    int y;  // y-coordinate of the bullet
    bool isOurBullet;  // Whether the bullet is ours or not
    bool wDown;  // Whether the W key is pressed
    bool sDown;  // Whether the S key is pressed
public:
    bool expired = false;  // Whether the bullet is expired or not
    // Constructor
    Bullet(SDL_Renderer* renderer, int x, int y, bool isOurBullet, bool wDown, bool sDown) {
        this->x = x;  // Set x-coordinate
        this->y = y;  // Set y-coordinate
        this->isOurBullet = isOurBullet;  // Set whether the bullet is ours or not
        this->wDown = wDown;  // Set whether the W key is pressed
        this->sDown = sDown;  // Set whether the S key is pressed
    }
    // Function to draw the bullet
    void draw(SDL_Renderer* renderer, SDL_Texture* texture) {
        SDL_Rect rect = { x, y, 10, 10 };  // Define the rectangle for the bullet
        SDL_RenderCopy(renderer, texture, NULL, &rect);  // Render the bullet
    }
    // Function to move the bullet
    void move() {
        if (isOurBullet) y -= 3 + (wDown ? 2 : 0);  // Move up if the bullet is ours
        else y += 3 + (sDown ? 2 : 0);  // Move down if the bullet is not ours

        if (y < 0 || y > 640) expired = true;  // Expire the bullet if it goes out of bounds
    }

    // move the bullet for the enemy
    void move2() {
        y += 3;
        if (y < 0 || y > 640) expired = true;  // Expire the bullet if it goes out of bounds
    }

    // Getter for x
    int getX() {
        return x;
    }

    // Getter for y
    int getY() {
        return y;
    }

    // getter for isEnemyBullet
    bool isItOurBullet() {
        return isOurBullet;
    }
};