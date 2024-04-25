// Ship class definition
#pragma once
#include<SDL.h>
class Ship {
private:
    int x;  // x-coordinate of the ship
    int y;  // y-coordinate of the ship
public:
    // Constructor
    Ship(SDL_Renderer* renderer) {
        x = 340;  // Initial x-coordinate
        y = 460;  // Initial y-coordinate
    }
    // Function to draw the ship
    void draw(SDL_Renderer* renderer, SDL_Texture* texture) {
        SDL_Rect rect = { x, y, 100, 100 };  // Define the rectangle for the ship
        SDL_RenderCopy(renderer, texture, NULL, &rect);  // Render the ship
    }

    void draw2(SDL_Renderer* renderer, SDL_Texture* texture, int i, int j, int height, int width) {
        SDL_Rect rect = { i, j, height, width };  // Define the rectangle for the enemy
        SDL_RenderCopy(renderer, texture, NULL, &rect);  // Render the enemy
    }
    // Function to move the ship
    void move(bool wDown, bool aDown, bool sDown, bool dDown) {

        if (aDown) x -= 2;  // Move left

        if (dDown) x += 2;  // Move right
    }
    // Getter for x
    int getX() {
        return x;
    }
    // Getter for y
    int getY() {
        return y;
    }

    // check for the boundary
    bool checkBoundary() {
        if (x < 0 || x > 800 || y < 0 || y > 600) {
            return true;
        }
        else {
            return false;
        }
    }


    void moveBoundary() {
        if (x < 0) {
            x = 800;
        }
        else if (x > 800) {
            x = 0;
        }
        else if (y < 0) {
            y = 600;
        }
        else if (y > 600) {
            y = 0;
        }
    }


};
