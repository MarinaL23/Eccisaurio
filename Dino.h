#ifndef DINO_H
#define DINO_H
#include "raylib.h"

// Clase que representa al dinosaurio controlado por el jugador
class Dino {
public:
    // Posición, velocidad y dimensiones del dinosaurio
    int x, y;
    int speedX, speedY;
    int width, height;
    bool isJumping;

    // Constructor con los valores iniciales del personaje
    Dino() {
        x = 50;
        y = 300;
        speedX = 0;
        speedY = 0;
        width = 40;
        height = 60;
        isJumping = false;
    }

    // Funcion para que el dinosaurio salte si está sobre el suelo
    void jump() {
        if (!isJumping) {
            speedY = -15; // Impulso hacia arriba (coordenadas invertidas en pantalla)
            isJumping = true;
        }
    }

    // Actualiza la posición del dinosaurio aplicando gravedad
    void update(int gravity, int groundLevel) {
        // Si está saltando, se modifica su posición vertical
        if (isJumping) {
            y += speedY;
            speedY += gravity;
        }
        // Evita que atraviese el suelo al caer
        if (y + height >= groundLevel) {
            y = groundLevel - height;
            speedY = 0;
            isJumping = false;
        }
    }

};

#endif //DINO_H
