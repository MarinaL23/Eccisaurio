#ifndef JUEGO_H
#define JUEGO_H
#include "Dino.h"
#include "Obstacle.h"
#include "Potion.h"
#include "raylib.h"
#include <vector>

class Juego {
    private:
    Dino tRex;
    std::vector<Obstacle> obstacles;
    std::vector<Potion> potions;
    int score;
    int lives;
    int gameSpeed;
    int ranking[5];

    bool isRunning;
    bool juegoIniciado;
    float sueloX = 0.0f;
    const int GRAVITY = 1;
    const int GROUND_LEVEL = 300;

    Texture2D dinoTextures[6];
    Texture2D dinoTex;
    Texture2D cactusSmallTex;
    Texture2D cactusLargeTex;
    Texture2D birdTex;

    Texture2D potionLifeTex;
    Texture2D potionDoubleTex;
    Texture2D potionShieldTex;
    Texture2D heartTex;
    Texture2D heart2Tex;
    Texture2D sueloTex;

    Texture2D scoreTex;
    Texture2D logoTex;
    Texture2D btnPlayTex;
    Rectangle botonPlay;

    int currentDinoSkin = 0;

public:
    Juego() {
        score = 0;
        lives = 3;
        gameSpeed = -6;
        isRunning = true;
        juegoIniciado = false;
        currentDinoSkin = 0;
        botonPlay = { 0, 0, 0, 0 };
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
