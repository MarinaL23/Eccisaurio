#ifndef DINO_H
#define DINO_H
#include "raylib.h"

class Dino {
public:
    int x, y;
    int speedX, speedY;
    int width, height;
    bool isJumping;

    Dino() {
        x = 50;
        y = 300;
        speedX = 0;
        speedY = 0;
        width = 40;
        height = 60;
        isJumping = false;
    }
    void jump() {
        if (!isJumping) {
            speedY = -15; // Impulso hacia arriba (coordenadas invertidas en pantalla)
            isJumping = true;
        }
    }

    void update(int gravity, int groundLevel) {
        if (isJumping) {
            y += speedY;
            speedY += gravity;
        }
        if (y + height >= groundLevel) {
            y = groundLevel - height;
            speedY = 0;
            isJumping = false;
        }
    }

};

#endif //DINO_H
