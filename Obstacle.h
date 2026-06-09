
#ifndef OBSTACLE_H
#define OBSTACLE_H

class Obstacle {
public:
    int x, y;
    int speedX, speedY;
    int width, height;

    Obstacle(int startX, int startY, int speed) {
        x = startX;
        y = startY;
        speedX = speed;
        speedY = 0;
        width = 30;
        height = 50;
    }
};

#endif //OBSTACLE_H