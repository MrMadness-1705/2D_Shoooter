#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<random>
#include<vector>
#include "bullet.h"
using namespace std;

// Enemy class definition

class Enemy {
protected:
    int x;  // x-coordinate of the enemy
    int y;  // y-coordinate of the enemy
    int behavior;  // Behavior of the enemy
    SDL_Renderer* renderer;  // Renderer for the enemy
    int fireCounter = 60;
public:
    // Constructor
    Enemy(SDL_Renderer* renderer) {
        x = rand() % 850;  // Initial x-coordinate
        y = -100;  // Initial y-coordinate
        behavior = 0;  // Initial behavior
    }
    // Function to draw the enemy
    void draw(SDL_Renderer* renderer, SDL_Texture* texture, vector<Bullet>& bullets) {
        fireCounter--;
        if (fireCounter <= 0) {
            fireCounter = 60;
            fire(bullets);
        }
        SDL_Rect rect = { x, y, 80, 80 };  // Define the rectangle for the enemy
        SDL_RenderCopy(renderer, texture, NULL, &rect);  // Render the enemy

    }

    void fire(vector<Bullet>& bullets) {
        bullets.push_back(Bullet(renderer, x + 50 - 5, y + 100, false, false, false));
    }




    // Function to move the enemy
    virtual void move() = 0;

    // Getter for x
    int getX() {
        return x;
    }
    // Getter for y
    int getY() {
        return y;
    }


};
class EnemyType1 : public Enemy{

public:
    EnemyType1(SDL_Renderer * renderer) : Enemy(renderer) {

        x = rand() % 850;  // Initial x-coordinate
        y = -100;  // Initial y-coordinate
        behavior = 0;  // Initial behavior
    }
    EnemyType1(SDL_Renderer * renderer, int x, int y) : Enemy(renderer) {
        this->x = x;
        this->y = y;
        behavior = 0;
    }
    //void move() override {
    //    // Different behaviors for the enemy
    //    // Behavior 0: Move right and down
    //    // Behavior 1: Move left and down
    //    // Behavior 2: Move right and up
    //    // Behavior 3: Move left and up
    //    if (behavior == 0) {
    //        x += 2;
    //        y += 2;
    //        if (x > 800) behavior = 1;
    //        if (y > 600) behavior = 2;
    //    }
    //    else if (behavior == 1) {
    //        x -= 2;
    //        y += 2;
    //        if (x < 0) behavior = 0;
    //        if (y > 600) behavior = 3;
    //    }
    //    else if (behavior == 2) {
    //        x += 2;
    //        y -= 2;
    //        if (x > 800) behavior = 3;
    //        if (y < 0) behavior = 0;
    //    }
    //    else if (behavior == 3) {
    //        x -= 2;
    //        y -= 2;
    //        if (x < 0) behavior = 2;
    //        if (y < 0) behavior = 1;
    //    }
    //}

    void move() override {
        if (behavior == 0) {
            y += 2;
            if (y > 330) behavior = 1;
        }
        else if (behavior == 1) {
            y -= 2;
            if (y < 0) behavior = 0;
        }
    }
};

class EnemyType2 : public Enemy {
public:
    EnemyType2(SDL_Renderer* renderer) : Enemy(renderer) {
        x = rand() % 850;  // Initial x-coordinate
        y = -100;  // Initial y-coordinate
        behavior = 0;  // Initial behavior

    }

    EnemyType2(SDL_Renderer* renderer, int x, int y) : Enemy(renderer) {
        this->x = x;
        this->y = y;
        behavior = 0;
    }
    void move() override {
        // Different behaviors for the enemy
        // Behavior 0: Move right and down
        // Behavior 1: Move left and down
        // Behavior 2: Move right and up
        // Behavior 3: Move left and up
        if (behavior == 0) {
            x += 2;
            if (x > 800) {
                behavior = 1;
                y += 20; // Move down when hitting the right edge
            }
        }
        else if (behavior == 1) {
            x -= 2;
            if (x < 0) {
                behavior = 0;
                y += 20; // Move down when hitting the left edge
            }
        }
    }
};