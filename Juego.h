#ifndef JUEGO_H
#define JUEGO_H
#include "Dino.h"
#include "Obstacle.h"
#include "Potion.h"
#include "raylib.h"
#include <vector>

// Clase principal del videojuego. Se encarga de controlar la lógica general,
// actualización de elementos y renderizado
class Juego {
private:
    Dino tRex;

    std::vector<Obstacle> obstacles;
    std::vector<Potion> potions;

    int score;
    int lives;
    int gameSpeed;
    int ranking[5];
    int frameCounter = 0;
    float doubleTimer;
    float shieldTimer;

    bool isRunning;
    bool juegoIniciado;
    bool doubleScore;
    bool shieldActive;

    float sueloX = 0.0f;
    const int GRAVITY = 1;
    const int GROUND_LEVEL = 300;

    Texture2D dinoCrouchTex;
    Texture2D dinoDeathTex;
    Texture2D dinoTex;
    Texture2D dino2Tex;
    Texture2D dinoUpTex;
    Texture2D dinoUp2Tex;
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
    // Constructor que inicializa los valores básicos del juego
    Juego() {
        score = 0;
        lives = 3;
        gameSpeed = -6;
        isRunning = true;
        juegoIniciado = false;
        doubleScore = false;
        shieldActive = false;
        doubleTimer = 0;
        shieldTimer = 0;
        currentDinoSkin = 0;
        botonPlay = { 0, 0, 0, 0 };

        for(int i = 0; i < 5; i++) {
            ranking[i] = 0;
        }
    }

    // Ejecuta el ciclo principal del videojuego
    void run();

private:
    // Procesa las entradas del usuario
    void processInput();
    void updateTimersPociones();
    void updateObstaculos();
    void updatePociones();
    void aplicarPocion(PotionType tipo);
    int puntosPorObstaculo();
    // Actualiza la lógica de todos los elementos del juego
    void update();
    // Verifica si existe colisión entre el dinosaurio y un obstáculo
    bool checkCollision(const Dino& d, const Obstacle& o);
    // Dibuja todos los elementos en pantalla
    void render();
    // Reinicia la partida cuando el jugador pierde todas las vidas
    void gameOver();
};

#endif //JUEGO_H
