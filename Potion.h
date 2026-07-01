#ifndef POTION_H
#define POTION_H

// Tipos de pociones disponibles en el juego
enum PotionType { LIVES, DOUBLE, SHIELD };


// Clase que representa los power-ups que puede recoger el jugador
class Potion {
public:
    // Posición, velocidad y dimensiones de la poción
    int x, y;
    int speedX;
    int width, height;
    PotionType type;
    bool active;

    // Constructor que inicializa la poción
    Potion(int startX, int startY, int speed, PotionType pType) {
        x = startX;
        y = startY;
        speedX = speed;
        width = 55;
        height = 55;
        type = pType;
        active = true;
    }

    // Actualiza la posición horizontal de la poción
    void update() {
        x += speedX;
    }

};
#endif