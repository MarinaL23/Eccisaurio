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
    bool isCrouching;

    // Constructor con los valores iniciales del personaje
    Dino() {
        x = 50;
        y = 242;
        speedX = 0;
        speedY = 0;
        width = 40;
        height = 50;
        isJumping = false;
        isCrouching = false;
    }

    // Funcion para que el dinosaurio salte si está sobre el suelo
    void jump() {
        if (!isJumping) {
            speedY = -15; // Impulso hacia arriba (coordenadas invertidas en pantalla)
            isJumping = true;
        }
    }
    // Funcion para que el dinosaurio se agache cuando ve un pterodáctilo
    void crouch(bool active) {
        if (!isJumping) {
            isCrouching = active;
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

        // si se agacha la altura cambia
        if (isCrouching) {
            height = 30; // Altura reducida al agacharse
        } else {
            height = 60; // Altura normal
        }
        
        if (isCrouching && !isJumping) {
            y = groundLevel - height;
        }
    }

};

#endif //DINO_H
