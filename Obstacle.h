
#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "raylib.h"

enum ObstacleType { CACTUS_SMALL, CACTUS_LARGE, BIRD };

class Obstacle {
public:
    int x, y;
    int speedX;
    int width, height;
    ObstacleType type;

    Obstacle(int startX, int startY, int speed, ObstacleType oType) {
        x = startX;
        speedX = speed;
        type = oType;
        // por definir la visualizacion de los tipos de obstaculos
        if (type == CACTUS_SMALL) {
            width = 30;
            height = 40;
            y = startY - height;
        } 
        else if (type == CACTUS_LARGE) {
            width = 50;
            height = 70;
            y = startY - height;
        } 
        else if (type == BIRD) {
            width = 50;
            height = 35;
            y = startY - 100;
        }
    }

    void update() {
        x += speedX;
    }

};

#endif //OBSTACLE_H