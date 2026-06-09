#ifndef JUEGO_H
#define JUEGO_H
#include "Dino.h"
#include "Obstacle.h"
#include "raylib.h"
#include <vector>

class Juego {
    private:
    Dino tRex;
    std::vector<Obstacle> obstacles;
    int score;
    int lives;
    int gameSpeed;
    int ranking[5];

    bool isRunning;
    const int GRAVITY = 1;
    const int GROUND_LEVEL = 300;

public:
    Juego() {
        score = 0;
        lives = 3;
        gameSpeed = -6;
        isRunning = true;
        for(int i = 0; i < 5; i++) ranking[i] = 0;
    }
    void run();
private:
    void processInput();
    void update();
    bool checkCollision(const Dino& d, const Obstacle& o);
    void render();
    void gameOver();
};

#endif //JUEGO_H
