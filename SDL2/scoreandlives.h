#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<string>
#include<iostream>
using namespace std;
class Score {
public:
    int score;
    Score() {
        score = 0;
    }

    void draw(SDL_Renderer* renderer, TTF_Font* font) {
        SDL_Color color = { 255, 0, 0 };
        SDL_Surface* surface = TTF_RenderText_Solid(font, ("Score " + to_string(score)).c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect rect = { 0, 0, 100, 100 };
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }

    void updateScore() {
        score++;
    }

    int getScore() {
        return score;
    }

    void updateScore(int score) {
        this->score += score;
    }
};

class Lives {
public:
    int lives;
    Lives() {
        lives = 3;
    }

    void draw(SDL_Renderer* renderer, TTF_Font* font) {
        SDL_Color color = { 255, 0, 0 };
        SDL_Surface* surface = TTF_RenderText_Solid(font, ("Lives " + to_string(lives)).c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        // draw the lives on the top right 
        SDL_Rect rect = { 750, 0, 100, 100 };
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }

    void updateLives() {
        lives--;
    }

    int getLives() {
        return lives;
    }

    void updateLives(int lives) {
        this->lives -= lives;
    }

    bool isdead() {
        if (lives == 0) {
            return true;
        }
        else {
            return false;
        }
    }
};