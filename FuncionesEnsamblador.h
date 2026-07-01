#ifndef ASM_FUNCS_H
#define ASM_FUNCS_H

extern "C"{
    int actualizarPuntuacion(int scoreActual, int vidasParaModificar);
    int actualizarVidas(int vidasActuales, int vidasParaModificar);
    int calcularVelocidad(int score);
}

#endif