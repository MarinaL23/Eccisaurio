#include "Joystick.h"
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>

Joystick::Joystick() : descriptorPuerto(-1), ultimoEstadoJoystick('N') {}

bool Joystick::conectar(const char* puerto) {
    descriptorPuerto = open(puerto, O_RDONLY | O_NOCTTY | O_NONBLOCK);
    if (descriptorPuerto < 0) return false;

    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    tcgetattr(descriptorPuerto, &tty);
    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO;
    tty.c_lflag &= ~ISIG;
    tcsetattr(descriptorPuerto, TCSANOW, &tty);
    return true;
}

char Joystick::leerEstado() {
    if (descriptorPuerto < 0) return 'N';
    char buffer[16];
    int n = read(descriptorPuerto, buffer, sizeof(buffer) - 1);
    if (n > 0) {
        for (int i = n - 1; i >= 0; i--) {
            if (buffer[i] == 'U' || buffer[i] == 'D' || buffer[i] == 'N') {
                ultimoEstadoJoystick = buffer[i];
                break;
            }
        }
    }
    return ultimoEstadoJoystick;
}

void Joystick::desconectar() {
    if (descriptorPuerto >= 0) close(descriptorPuerto);
}