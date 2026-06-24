#ifndef JOYSTICK_H
#define JOYSTICK_H

class Joystick {
private:
    int descriptorPuerto;
    char ultimoEstadoJoystick;

public:
    Joystick();
    bool conectar(const char* puerto);
    char leerEstado();
    void desconectar();
};

#endif