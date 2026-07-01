#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "raylib.h"

// Tipos de obstáculos que pueden aparecer durante la partida
enum ObstacleType { CACTUS_SMALL, CACTUS_LARGE, BIRD };


// Clase que representa los obstáculos que debe esquivar el jugador
class Obstacle {
public:
    // Posición, velocidad y dimensiones del obstáculo
    int x, y;
    int speedX;
    int width, height;
    ObstacleType type;

    // Constructor que inicializa el obstáculo según su tipo
    Obstacle(int startX, int startY, int speed, ObstacleType oType) {
        x = startX;
        speedX = speed;
        type = oType;

        // Define el tamaño y la posición inicial según el tipo.
        if (type == CACTUS_SMALL) {
            width = 30;
            height = 30;
            y = startY - height;
        } 
        else if (type == CACTUS_LARGE) {
            width = 50;
            height = 30;
            y = startY - height;
        } 
        else if (type == BIRD) {
            width = 50;
            height = 30;
            y = startY - 80;
        }
    }

    
    // Actualiza la posición horizontal del obstáculo
    void update() {
        x += speedX;
    }

};

#endif //OBSTACLE_H