#include "Juego.h"

// Crea una instancia del juego y ejecuta el ciclo principal
int main() {
    Juego Juego;
    Juego.musica = LoadMusicStream("music/macarena-.mp3");
    Juego.musica.looping = true;
    PlayMusicStream(Juego.musica);

    Juego.run();
    UnloadMusicStream(Juego.musica);
    return 0;
}