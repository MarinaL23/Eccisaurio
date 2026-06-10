#include "Juego.h"
#include "Obstacle.h"

void DibujarRedimensionado(Texture2D textura, float xDestino, float yDestino, float anchoDestino, float altoDestino, Color tinte) {
    Rectangle source = { 0.0f, 0.0f, (float)textura.width, (float)textura.height };
    Rectangle dest = { xDestino, yDestino, anchoDestino, altoDestino };
    Vector2 origin = { 0.0f, 0.0f };
    DrawTexturePro(textura, source, dest, origin, 0.0f, tinte);
}

void Juego::run(){
    InitWindow(800, 400, "Eccisaurio");
    SetTargetFPS(60);

    dinoTex = LoadTexture("png/dino.png");
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

    botonPlay.width = btnPlayTex.width * 0.15f;
    botonPlay.height = btnPlayTex.height * 0.15f;
    botonPlay.x = 400 - (botonPlay.width / 2);
    botonPlay.y = 250 - (botonPlay.height / 2);

    if(obstacles.empty()) {
        obstacles.push_back(Obstacle(650, GROUND_LEVEL, gameSpeed, CACTUS_SMALL));
    }

    while (!WindowShouldClose() && isRunning) {
        processInput();
        update();
        render();
    }

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

    CloseWindow();
}

void Juego::processInput(){
    if (!juegoIniciado) {
        Vector2 mousePos = GetMousePosition();
        if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, botonPlay))
            || IsKeyPressed(KEY_ENTER)) {
            juegoIniciado = true;
        }
    } else {
        if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP)) {
            tRex.jump();
        }
    }
}

void Juego::update(){
    if (juegoIniciado) {
        tRex.update(GRAVITY, GROUND_LEVEL);

        sueloX += gameSpeed; 
        if (sueloX <= -800) { 
            sueloX = 0;
        }

        for (size_t i = 0; i < obstacles.size(); i++) {
            obstacles[i].update();

            if (checkCollision(tRex, obstacles[i])) {
                lives--;
                obstacles.erase(obstacles.begin() + i);

                if (lives <= 0) {
                    gameOver();
                } else {
                    obstacles.push_back(Obstacle(850, GROUND_LEVEL, gameSpeed, CACTUS_SMALL));
                }

                break;
            }
            if (obstacles[i].x + obstacles[i].width < 0) {
                obstacles.erase(obstacles.begin() + i);
                obstacles.push_back(Obstacle(850, GROUND_LEVEL, gameSpeed, CACTUS_SMALL));
                score += 10;
                break;
            }
        }
    }
}

bool Juego::checkCollision(const Dino& d, const Obstacle& o){
    Rectangle dino = {d.x, d.y, d.width, d.height};
    Rectangle obstaculo = {o.x, o.y, o.width, o.height};

    return CheckCollisionRecs(dino, obstaculo);
}
void Juego::render(){
    BeginDrawing();
        ClearBackground(RAYWHITE); 

        DibujarRedimensionado(sueloTex, sueloX, GROUND_LEVEL, 800, 40, WHITE);
        DibujarRedimensionado(sueloTex, sueloX + 800, GROUND_LEVEL, 800, 40, WHITE);
        
        float dinoW = dinoTex.width * 0.08f;
        float dinoH = dinoTex.height * 0.08f;
        DibujarRedimensionado(dinoTex, tRex.x, tRex.y, dinoW, dinoH, WHITE);

        float cactusW = cactusSmallTex.width * 0.07f;
        float cactusH = cactusSmallTex.height * 0.07f;
        for (size_t i = 0; i < obstacles.size(); i++) {
            DibujarRedimensionado(cactusSmallTex, obstacles[i].x, obstacles[i].y, cactusW, cactusH, WHITE);
        }

        float scoreW = scoreTex.width * 0.15f;
        float scoreH = scoreTex.height * 0.15f;
        DibujarRedimensionado(scoreTex, 500, -30, scoreW, scoreH, WHITE);
        DrawText(TextFormat("%05d", score), 690, 37, 25, DARKGRAY);

        float heartW = heartTex.width * 0.08f;
        float heartH = heartTex.height * 0.08f;
        for (int i = 0; i < 3; i++) {
            if (i < lives) {
                DibujarRedimensionado(heartTex, -5 + (i * 30), 5, heartW, heartH, WHITE);
            } else {
                DibujarRedimensionado(heart2Tex, -5 + (i * 30), 5, heartW, heartH, WHITE);
            }
        }
        
        if (!juegoIniciado) {
            float factorEscala = 0.25f; 
            float logoW = logoTex.width * factorEscala;
            float logoH = logoTex.height * factorEscala;
            DibujarRedimensionado(logoTex, 400 - (logoW / 2), 4, logoW, logoH, WHITE);
            DibujarRedimensionado(btnPlayTex, botonPlay.x, botonPlay.y, botonPlay.width, botonPlay.height, WHITE);
        }

    EndDrawing();
}

void Juego::gameOver() {
    juegoIniciado = false;
    lives = 3;
    score = 0;
    obstacles.clear();
    obstacles.push_back(Obstacle(650, GROUND_LEVEL, gameSpeed, CACTUS_SMALL));
}