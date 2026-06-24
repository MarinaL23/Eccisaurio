#include "Juego.h"
#include "Obstacle.h"
#include "FuncionesEnsamblador.h"
#include "Joystick.h"
#include <iostream>

Joystick joystick;
char estadoJoystickAnterior = 'N';

// Función auxiliar para dibujar una textura con el tamaño que se indique
void DibujarRedimensionado(Texture2D textura, float xDestino, float yDestino, float anchoDestino, float altoDestino, Color tinte) {
    Rectangle source = { 0.0f, 0.0f, (float)textura.width, (float)textura.height };
    Rectangle dest = { xDestino, yDestino, anchoDestino, altoDestino };
    Vector2 origin = { 0.0f, 0.0f };
    DrawTexturePro(textura, source, dest, origin, 0.0f, tinte);
}

// Inicializa la ventana, carga las texturas y ejecuta el ciclo principal del juego
void Juego::run(){
    InitWindow(800, 400, "Eccisaurio");
    SetTargetFPS(60);

    // Carga las texturas del personaje, obstáculos, pociones e interfaz
    dinoTex = LoadTexture("png/dino.png");
    dinoCrouchTex = LoadTexture("png/agacharse.png");
    dinoDeathTex = LoadTexture("png/died.png");
    dino2Tex = LoadTexture("png/dino2.png");
    dinoUpTex = LoadTexture("png/dinoup.png");
    dinoUp2Tex = LoadTexture("png/dinoup2.png");
    cactusSmallTex = LoadTexture("png/cactus.png");
    cactusLargeTex = LoadTexture("png/cactus2.png");
    birdTex = LoadTexture("png/pterosaur.png");
    potionLifeTex = LoadTexture("png/potion1.png");
    potionDoubleTex = LoadTexture("png/potion2.png");
    potionShieldTex = LoadTexture("png/potion3.png");
    
    scoreTex = LoadTexture("png/score.png");
    logoTex = LoadTexture("png/name.png"); 
    btnPlayTex = LoadTexture("png/play.png");
    heartTex = LoadTexture("png/heart.png");
    heart2Tex = LoadTexture("png/heart2.png");
    sueloTex = LoadTexture("png/road.png");

    // Se ajusta el tamaño y la posición del botón de inicio
    botonPlay.width = btnPlayTex.width * 0.15f;
    botonPlay.height = btnPlayTex.height * 0.15f;
    botonPlay.x = 400 - (botonPlay.width / 2);
    botonPlay.y = 250 - (botonPlay.height / 2);

    if (!joystick.conectar("/dev/ttyACM0")) {
    std::cout << "No se pudo conectar el joystick, se usara solo el teclado.\n";
    }
    // Se crea el primer obstáculo al iniciar el juego
    if(obstacles.empty()) {
        obstacles.push_back(Obstacle(650, GROUND_LEVEL, gameSpeed, CACTUS_SMALL));
    }

    // Ciclo principal del videojuego
    while (!WindowShouldClose() && isRunning) {
        processInput();
        update();
        render();
    }

    // Se liberan las texturas antes de cerrar el programa
    UnloadTexture(heartTex);
    UnloadTexture(heart2Tex);
    UnloadTexture(sueloTex);
    UnloadTexture(logoTex);
    UnloadTexture(btnPlayTex);
    UnloadTexture(dinoTex);
    UnloadTexture(cactusSmallTex);
    UnloadTexture(cactusLargeTex);
    UnloadTexture(birdTex);
    UnloadTexture(potionLifeTex);
    UnloadTexture(potionDoubleTex);
    UnloadTexture(potionShieldTex);
    
    joystick.desconectar();
    CloseWindow();
}

// Procesa las entradas del usuario, tanto en el menú como durante la partida
void Juego::processInput(){
    if (!juegoIniciado) {
        Vector2 mousePos = GetMousePosition();

        // Inicia el juego con clic en Play o con Enter
        if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, botonPlay))
            || IsKeyPressed(KEY_ENTER)) {
            juegoIniciado = true;
        }
    } else {
        // Hace saltar al dinosaurio durante la partida
        char estadoJoystick = joystick.leerEstado();
        bool saltoJoystick = (estadoJoystick == 'U' && estadoJoystickAnterior != 'U');
        bool agacharJoystick = (estadoJoystick == 'D');

        if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP) || saltoJoystick) {
            tRex.jump();
        }
        // Hace que el dinosaurio se agache
        if (IsKeyDown(KEY_DOWN) || agacharJoystick) {
            tRex.crouch(true);
        } else {
            tRex.crouch(false);
        }

        estadoJoystickAnterior = estadoJoystick;
    }
}

void Juego::updateTimersPociones() {
    float delta = GetFrameTime();

    if (doubleScore) {
        doubleTimer -= delta;

        if (doubleTimer <= 0) {
            doubleScore = false;
            doubleTimer = 0;
        }
    }

    if (shieldActive) {
        shieldTimer -= delta;

        if (shieldTimer <= 0) {
            shieldActive = false;
            shieldTimer = 0;
        }
    }
}


void Juego::updateObstaculos() {
    for (size_t i = 0; i < obstacles.size(); i++) {
        obstacles[i].update();

        // Si el dinosaurio choca, pierde una vida
        if (checkCollision(tRex, obstacles[i])) {
            if (!shieldActive) {
                lives = actualizarVidas(lives, -1);
            }
            obstacles.erase(obstacles.begin() + i);

            if (lives <= 0) {
                gameOver();
            } else {
                obstacles.push_back(Obstacle(850, GROUND_LEVEL, gameSpeed, CACTUS_SMALL));
            }

            break;
        }
        // Si el obstáculo sale de pantalla, se elimina y se genera otro
        if (obstacles[i].x + obstacles[i].width < 0) {
            obstacles.erase(obstacles.begin() + i);
            // Obstaculos aleatorios
            int randomTipo = GetRandomValue(0, 2);
            obstacles.push_back(Obstacle(850, GROUND_LEVEL, gameSpeed, (ObstacleType)randomTipo));
            if (GetRandomValue(1, 10) <= 3) { 
                int tipoPocion = GetRandomValue(0, 2);
                int potionX = GetRandomValue(900, 1100);
                int potionY = GetRandomValue(GROUND_LEVEL - 140, GROUND_LEVEL - 45);
                potions.push_back(Potion(potionX, potionY, gameSpeed, (PotionType)tipoPocion));
            }
            score = actualizarPuntuacion(score, puntosPorObstaculo());
            break;
        }
    }
}


void Juego::updatePociones() {
    for (size_t i = 0; i < potions.size(); i++) {
        potions[i].update();

        Rectangle dino = {
            (float)tRex.x,
            (float)tRex.y,
            (float)tRex.width,
            (float)tRex.height
        };

        Rectangle potion = {
            (float)potions[i].x,
            (float)potions[i].y,
            (float)potions[i].width,
            (float)potions[i].height
        };

        if (CheckCollisionRecs(dino, potion)) {
            aplicarPocion(potions[i].type);
            potions.erase(potions.begin() + i);
            break;
        }

        if (potions[i].x + potions[i].width < 0) {
            potions.erase(potions.begin() + i);
            break;
        }
    }
}


void Juego::aplicarPocion(PotionType tipo) {
    if (tipo == LIVES) {
        if (lives < 3) {
            lives = actualizarVidas(lives, 1);
        }
    } 
    else if (tipo == DOUBLE) {
        doubleScore = true;
        doubleTimer = 5.0f;
    } 
    else if (tipo == SHIELD) {
        shieldActive = true;
        shieldTimer = 5.0f;
    }
}


int Juego::puntosPorObstaculo() {
    if (doubleScore) {
        return 20;
    }

    return 10;
}

// Actualiza la lógica del juego, dinosaurio, suelo, obstáculos y colisiones
void Juego::update(){
    if (juegoIniciado) {
        frameCounter++;
        updateTimersPociones();
        tRex.update(GRAVITY, GROUND_LEVEL);

        // Movimiento del suelo para simular desplazamiento
        sueloX += gameSpeed; 
        if (sueloX <= -800) { 
            sueloX = 0;
        }

        updateObstaculos();
        updatePociones();
    }
}


// Verifica si el dinosaurio y un obstáculo se están tocando
bool Juego::checkCollision(const Dino& d, const Obstacle& o){
    Rectangle dino = {(float)d.x, (float)d.y, (float)d.width, (float)d.height};
    Rectangle obstaculo = {(float)o.x, (float)o.y, (float)o.width, (float)o.height};

    return CheckCollisionRecs(dino, obstaculo);
}

// Dibuja todos los elementos del juego en pantalla
void Juego::render(){
    BeginDrawing();
    ClearBackground(RAYWHITE); 

    // Dibujo del suelo duplicado para dar efecto de movimiento continuo
    DibujarRedimensionado(sueloTex, sueloX, GROUND_LEVEL, 800, 40, WHITE);
    DibujarRedimensionado(sueloTex, sueloX + 800, GROUND_LEVEL, 800, 40, WHITE);
        
    // Dibujo del dinosaurio
    float dinoW = dinoTex.width * 0.08f;
    float dinoH = dinoTex.height * 0.08f;
    if (tRex.isCrouching) {
        // Aquí cargarías o usarías la textura agachada (dinoCrouchTex)
        DibujarRedimensionado(dinoCrouchTex, tRex.x, tRex.y, dinoW, dinoH - 12, WHITE);
    } else {
        // Dibujamos la textura normal, hace que los pies se muevan
        if ((frameCounter / 10) % 2 == 0) {
            DibujarRedimensionado(dinoTex, tRex.x, tRex.y, dinoW, dinoH + 10, WHITE);
        } else {
            DibujarRedimensionado(dino2Tex, tRex.x, tRex.y, dinoW, dinoH + 10, WHITE);
        }
    }
    
    // Dibujo de los obstáculos
    float cactusW = cactusSmallTex.width * 0.07f;
    float cactusH = cactusSmallTex.height * 0.07f;
    for (size_t i = 0; i < obstacles.size(); i++) {
        Texture2D texActual;
        float escala = 0.07f;
        // Seleccionar textura y ajustar tamaño según el tipo
        switch (obstacles[i].type) {
            case CACTUS_SMALL: texActual = cactusSmallTex; break;
            case CACTUS_LARGE: texActual = cactusLargeTex; break;
            case BIRD: texActual = birdTex; break;
        }
        DibujarRedimensionado(texActual, obstacles[i].x, obstacles[i].y,
                texActual.width * escala,texActual.height * escala, WHITE);
    }

    for (const auto& p : potions) {
        Texture2D texActual;
        switch (p.type) {
            case LIVES:  texActual = potionLifeTex; break;
            case DOUBLE: texActual = potionDoubleTex; break;
            case SHIELD: texActual = potionShieldTex; break;
        }
        DibujarRedimensionado(texActual, (float)p.x, (float)p.y, (float)p.width, (float)p.height, WHITE);
    }

    // Dibujo del puntaje
    float scoreW = scoreTex.width * 0.15f;
    float scoreH = scoreTex.height * 0.15f;
    DibujarRedimensionado(scoreTex, 500, -30, scoreW, scoreH, WHITE);
    DrawText(TextFormat("%05d", score), 690, 37, 25, DARKGRAY);

    // Dibujo de las vidas
    float heartW = heartTex.width * 0.08f;
    float heartH = heartTex.height * 0.08f;
    for (int i = 0; i < 3; i++) {
        if (i < lives) {
            DibujarRedimensionado(heartTex, -5 + (i * 30), 5, heartW, heartH, WHITE);
        } else {
            DibujarRedimensionado(heart2Tex, -5 + (i * 30), 5, heartW, heartH, WHITE);
        }
    }

    // Muestra en pantalla las pociones activas
    if (doubleScore) {
        DibujarRedimensionado(potionDoubleTex, 120, 10, 30, 30, WHITE);
        DrawText(TextFormat("%.1f", doubleTimer), 155, 18, 18, DARKGRAY);
    }

    if (shieldActive) {
        DibujarRedimensionado(potionShieldTex, 120, 45, 30, 30, WHITE);
        DrawText(TextFormat("%.1f", shieldTimer), 155, 53, 18, DARKGRAY);
    }
        
    // Pantalla inicial del juego
    if (!juegoIniciado) {
        float factorEscala = 0.25f; 
        float logoW = logoTex.width * factorEscala;
        float logoH = logoTex.height * factorEscala;
        DibujarRedimensionado(logoTex, 400 - (logoW / 2), 4, logoW, logoH, WHITE);
        DibujarRedimensionado(btnPlayTex, botonPlay.x, botonPlay.y, botonPlay.width, botonPlay.height, WHITE);
    }

    EndDrawing();
}

// Reinicia los valores principales cuando el jugador pierde todas las vidas
void Juego::gameOver() {
    juegoIniciado = false;
    lives = 3;
    score = 0;
    obstacles.clear();
    obstacles.push_back(Obstacle(650, GROUND_LEVEL, gameSpeed, CACTUS_SMALL));
    doubleScore = false;
    shieldActive = false;
    doubleTimer = 0;
    shieldTimer = 0;
    potions.clear();
}