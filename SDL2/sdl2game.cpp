#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include<random>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<ctime>
#include <vector>
#include <string>



using namespace std;

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

// Ship class definition
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
        if (wDown) y -= 2;  // Move up
        if (aDown) x -= 2;  // Move left
        //  if (sDown) y += 2;  // Move down
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

class EnemyType1 : public Enemy {

public:
    EnemyType1(SDL_Renderer* renderer) : Enemy(renderer) {

        x = rand() % 850;  // Initial x-coordinate
        y = -100;  // Initial y-coordinate
        behavior = 0;  // Initial behavior
    }
    EnemyType1(SDL_Renderer* renderer, int x, int y) : Enemy(renderer) {
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
            if (y > 450) behavior = 1;
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

class Score {
public:
    int score;
    Score() {
        score = 0;
    }

    void draw(SDL_Renderer* renderer, TTF_Font* font) {
        SDL_Color color = { 255, 255, 255 };
        SDL_Surface* surface = TTF_RenderText_Solid(font, ("Score: " + to_string(score)).c_str(), color);
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
        SDL_Color color = { 255, 255, 255 };
        SDL_Surface* surface = TTF_RenderText_Solid(font, ("Lives: " + to_string(lives)).c_str(), color);
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

enum class GameState {
    MENU,
    PLAY,
    EXIT
};



// Main function
int main(int argc, char** argv)
{
    const int SCREEN_WIDTH = 850;
    const int SCREEN_HEIGHT = 640;
    // Create the window and the renderer
    SDL_Window* window = SDL_CreateWindow("Space game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 850, 640, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // Initialize spawn timer delay
    float spawnTimer = 5.0f;
    float timeElapsed = 0.0f;

    // Load the textures
    SDL_Texture* backgroundTexture = IMG_LoadTexture(renderer, "bg.jpg");
    SDL_Texture* shipTexture = IMG_LoadTexture(renderer, "ship2.png");
    SDL_Texture* enemyTexture = IMG_LoadTexture(renderer, "enemy.png");
    SDL_Texture* bulletTexture = IMG_LoadTexture(renderer, "bullet.png");
    SDL_Texture* enemy2Texture = IMG_LoadTexture(renderer, "enemyBlue1.png");


    // Images for the bottom tile map

    SDL_Surface* grass = IMG_Load("grass.jpg");

    SDL_Texture * tile = SDL_CreateTextureFromSurface(renderer, grass);


    

    // Initialize TTF
    TTF_Init();
    if (TTF_Init() < 0) {
        cout << "Error: " << TTF_GetError() << endl;
    }

    // Initialize SDL_mixer
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music* music = Mix_LoadMUS("background.mp3");
    Mix_Chunk* cannon = Mix_LoadWAV("cannonshot.wav");

    // load the font
    TTF_Font* font = TTF_OpenFont("fnt.otf", 24);
    if (font == NULL) {
        cerr
            << "Failed to load font." << endl;
    }


    // Define the time step
    Uint32 time_step_ms = 1000 / 60;
    float time_step_s = time_step_ms / 1000.0;
    Uint32 next_game_step = SDL_GetTicks();

    // Define the random number generator
    mt19937 rng;
    rng.seed(time(NULL));
    uniform_int_distribution<int> xDist(0, 800);
    uniform_int_distribution<int> yDist(0, 600);

    // Create the ship and the enemies
    Ship ship(renderer);
    vector<Enemy*> enemies;
    vector<Bullet> bullets;

    // Create the game logic
    GameLogic gameLogic;

    // Create the score
    Score score;

    // Create the lives
    Lives lives;

    // Define the game state
    bool isMenu = true;
    bool isPlay = false;
    bool isEnd = false;


    /*for (int i = 0; i < 10; i++) {
        int x = xDist(rng);
        int y = yDist(rng);
        if (i % 2 == 0)
            enemies.push_back(new EnemyType1(renderer, x, y));
        else
        enemies.push_back(new EnemyType2(renderer, x, y));

    }*/

    // Define the tile map for the bottom of the screen
    int TileMap[10][10] = {
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    // Define the tile map for the ground of the screen
    int TileMap2[10][10] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    // Define the key states
    bool wDown = false;
    bool aDown = false;
    bool sDown = false;
    bool dDown = false;

    // Play the music
    Mix_PlayMusic(music, -1);

    // Game loop
    while (true) {
        // Delay the game to match the time step
        Uint32 now = SDL_GetTicks();
        if (next_game_step > now) {
            SDL_Delay(next_game_step - now);
        }
        next_game_step += time_step_ms;

        // Update the spawn timer
        timeElapsed += time_step_s;


        // Spawn a new enemy if the spawn timer is expired
        if (timeElapsed > spawnTimer) {
            int x = xDist(rng);
            int y = -20;
            if (rand() % 2 == 0)
                enemies.push_back(new EnemyType1(renderer, x, y));
            else
                enemies.push_back(new EnemyType2(renderer, x, y));
            timeElapsed = 0.0f;
        }


        // Handle events
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_w) wDown = true;
                if (event.key.keysym.sym == SDLK_a) aDown = true;
                if (event.key.keysym.sym == SDLK_s) sDown = true;
                if (event.key.keysym.sym == SDLK_d) dDown = true;
                if (event.key.keysym.sym == SDLK_SPACE) {
                    bullets.push_back(Bullet(renderer, ship.getX() + 50 - 5, ship.getY(), true, wDown, sDown));
                    Mix_PlayChannel(-1, cannon, 0);
                }
            }
            else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_w) wDown = false;
                if (event.key.keysym.sym == SDLK_a) aDown = false;
                if (event.key.keysym.sym == SDLK_s) sDown = false;
                if (event.key.keysym.sym == SDLK_d) dDown = false;
            }
        }

        // Move the ship
        ship.move(wDown, aDown, sDown, dDown);

        // Clear the renderer
        SDL_RenderClear(renderer);

        if (isMenu) {
            SDL_Surface* surface = IMG_Load("background.png");

            // Create a texture from the surface
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

            // draw the texture
            SDL_RenderCopy(renderer, texture, NULL, NULL);

            // Present the renderer
           // SDL_RenderPresent(renderer);

            // draw the text
            SDL_Color color = { 255, 255, 255 };
            SDL_Surface* surface2 = TTF_RenderText_Solid(font, "Enter to Start", color);
            SDL_Surface* surface3 = TTF_RenderText_Solid(font, "Exit", color);

            // Create textures from the surfaces
            SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
            SDL_Texture* texture3 = SDL_CreateTextureFromSurface(renderer, surface3);
           
            // Define where to draw the text
            SDL_Rect rect2 = { 350, 200, 150, 120 };  // Adjust these values as needed
            SDL_Rect rect3 = { 340, 300, 100, 100 };  // Adjust these values as needed
           
            // Draw the text
            SDL_RenderCopy(renderer, texture2, NULL, &rect2);
            SDL_RenderCopy(renderer, texture3, NULL, &rect3);
       

            // Present the renderer
            SDL_RenderPresent(renderer);
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    isPlay = false;
                }
                else if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_RETURN) {
                        isMenu = false;  // Exit the menu
                        isPlay = true;  // Enter the game state
                    }
                    else if (event.key.keysym.sym == SDLK_ESCAPE) {
                        isPlay = false;  // Exit the game
                        exit(1);
                    }
                }
            }
        }
        else if (isPlay) {
            // Render the background
            SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

            // Draw the tile map
            

            for (int i = 0; i < 10; i++) {
     for (int j = 0; j < 10; j++) {
         if (TileMap[i][j] == 1) {
             SDL_Rect rect = { j * 16, SCREEN_HEIGHT - (10-i) * 18, 18, 18 };
             SDL_RenderCopy(renderer, tile, NULL, &rect);
         }
     }
 }




            

            // check for the collision between the ship and the enemy

            for (int i = 0; i < enemies.size(); i++) {
                if (gameLogic.checkCollision(ship, *enemies[i])) {
                    //cout << "Game Over" << endl;
                    lives.updateLives();
                    enemies.erase(enemies.begin() + i);
                    i--;
                    if (lives.isdead()) {
                        isPlay = false;
                        isEnd = true;
                    }


                }
            }

            // check for the collision between the bullet and the enemy
            for (int i = 0; i < enemies.size(); i++) {
                for (int j = 0; j < bullets.size(); j++) {
                    if (!bullets[j].isItOurBullet()) {
                        continue;
                    }
                    if (gameLogic.checkCollision(bullets[j], *enemies[i])) {
                        enemies.erase(enemies.begin() + i);
                        bullets.erase(bullets.begin() + j);
                        score.updateScore(10);
                        i--;
                        break;
                    }
                }



            }

            // check for the collision between the bullet and the ship
            for (int i = 0; i < bullets.size(); i++) {
                if (bullets[i].isItOurBullet()) {
                    continue;
                }
                if (gameLogic.checkCollision(bullets[i], ship)) {
                    lives.updateLives();
                    bullets.erase(bullets.begin() + i);
                    i--;
                    if (lives.isdead()) {
						isPlay = false;
						isEnd = true;
					}
                    cout << "Game Over" << endl;
                }
            }



            for (int i = 0; i < enemies.size(); i++) {
                if (dynamic_cast<EnemyType1*>(enemies[i])) {
                    enemies[i]->draw(renderer, enemyTexture, bullets);

                }
                else if (dynamic_cast<EnemyType2*>(enemies[i])) {
                    enemies[i]->draw(renderer, enemy2Texture, bullets);

                }
                enemies[i]->move();
            }

            // Draw the ship
            ship.draw2(renderer, shipTexture, ship.getX(), ship.getY(), 100, 100);
            ship.moveBoundary();

            // Move and draw the bullets
            for (int i = 0; i < bullets.size(); i++) {
                bullets[i].move();
                bullets[i].draw(renderer, bulletTexture);
                if (bullets[i].expired) {
                    bullets.erase(bullets.begin() + i);
                    i--;
                }
            }

            for (Bullet& bullet : bullets) {
                bullet.move();
                bullet.draw(renderer, bulletTexture);
            }

            // Draw the score
            score.draw(renderer, font);
            // Draw the lives
            lives.draw(renderer, font);
            // Present the renderer
            SDL_RenderPresent(renderer);
        }
        else if (isEnd) {
            SDL_Surface* end = IMG_Load("bg.jpg");
            SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, end);
            if (texture == NULL) {
				cout << "Error: " << SDL_GetError() << endl;
			}

            // draw the texture
            SDL_RenderCopy(renderer, texture, NULL, NULL);

            // Present the renderer
            SDL_RenderPresent(renderer);

            // draw the text
            SDL_Color color = { 255, 255, 255 };
            SDL_Surface* surface2 = TTF_RenderText_Solid(font, "Enter to Restart", color);
            SDL_Surface* surface3 = TTF_RenderText_Solid(font, "Exit", color);
            SDL_Surface* surface4 = TTF_RenderText_Solid(font, ("Score: " + to_string(score.getScore())).c_str(), color);

            // Create textures from the surfaces
            SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
            SDL_Texture* texture3 = SDL_CreateTextureFromSurface(renderer, surface3);
            SDL_Texture* texture4 = SDL_CreateTextureFromSurface(renderer, surface4);

            // Define where to draw the text
            SDL_Rect rect2 = { 350, 200, 150, 120 };  // Adjust these values as needed
            SDL_Rect rect3 = { 340, 300, 100, 100 };  // Adjust these values as needed
            SDL_Rect rect4 = { 340, 400, 100, 100 };  // Adjust these values as needed

            // Draw the text
            SDL_RenderCopy(renderer, texture2, NULL, &rect2);
            SDL_RenderCopy(renderer, texture3, NULL, &rect3);
            SDL_RenderCopy(renderer, texture4, NULL, &rect4);

            // Present the renderer
            SDL_RenderPresent(renderer);
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
					isPlay = false;
				}
                else if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_RETURN) {
						isMenu = true;  // Exit the menu
						isPlay = false;  // Enter the game state
						isEnd = false;
						lives.lives = 3;
						score.score = 0;
						enemies.clear();
						bullets.clear();
					}
                    else if (event.key.keysym.sym == SDLK_ESCAPE) {
						isPlay = false;  // Exit the game
						exit(1);
                        Mix_FreeMusic(music);
                        Mix_Quit();
					}
				}
			}
        }

    }
    return 0;

    }