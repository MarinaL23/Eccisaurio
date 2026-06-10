#ifndef POTION_H
#define POTION_H

enum PotionType { LIVES, DOUBLE, SHIELD };

class Potion {
public:
    int x, y;
    int speedX;
    int width, height;
    PotionType type;
    bool active;

    Potion(int startX, int startY, int speed, PotionType pType) {
        x = startX;
        y = startY;
        speedX = speed;
        width = 25;
        height = 25;
        type = pType;
        active = true;
    }

    void update() {
        x += speedX;
    }

};
#endif