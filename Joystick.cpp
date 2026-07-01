#include "Joystick.h"
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

Joystick::Joystick() : descriptorPuerto(-1), ultimoEstadoJoystick('N') {}

//Conecta con el puerto serial del Arduino
bool Joystick::conectar(const char* puerto) {
    //Intenta abrir el puerto en modo lectura no bloqueante
    descriptorPuerto = open(puerto, O_RDONLY | O_NOCTTY | O_NONBLOCK);
    
    //Si falla, retorna false
    if(descriptorPuerto < 0){
        std::cerr << "Error: No se pudo abrir el puerto " << puerto << std::endl;
        return false;
    }

    //Configura los parámetros del puerto serial
    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    
    //Lee la configuración actual del puerto
    if (tcgetattr(descriptorPuerto, &tty) != 0) {
        std::cerr << "Error: No se pudo leer la configuración del puerto" << std::endl;
        close(descriptorPuerto);
        descriptorPuerto = -1;
        return false;
    }
    
    cfsetispeed(&tty, B9600);//Velocidad de entrada para recibir datos
    cfsetospeed(&tty, B9600);//Velocidad de salida  para recibir datos
    
    //Configuración de control para poder leer del arduino
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO;
    tty.c_lflag &= ~ISIG;
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    
    if(tcsetattr(descriptorPuerto, TCSANOW, &tty) != 0){
        std::cerr << "Error: No se pudo aplicar la configuración del puerto" << std::endl;
        close(descriptorPuerto);
        descriptorPuerto = -1;
        return false;
    }
    
    tcflush(descriptorPuerto, TCIFLUSH);//elimina datos previos)

    
    std::cout << "El Joystick ha sido conectado de forma exitosa en el puerto: " << puerto << std::endl;
    return true;
}

//Lee el estado actual del joystick desde el puerto serial
char Joystick::leerEstado(){
    //Si no hay conexión, retorna el último estado conocido
    if (descriptorPuerto < 0){
        return ultimoEstadoJoystick;
    }
    //Buffer para almacenar los datos leídos
    unsigned char buffer[64];
    int n = read(descriptorPuerto, buffer, sizeof(buffer));
    
    //Si se leyeron datos, procesa el último carácter válido
    if (n > 0) {
        for (int i = n - 1; i >= 0; i--) {
            char c = buffer[i];
            
            //Verifica si es un carácter válido (U, D, o N)
            if (c == 'U' || c == 'D' || c == 'N') {
                ultimoEstadoJoystick = c;
                return ultimoEstadoJoystick;
            }
        }
    }
    
    return ultimoEstadoJoystick;//Si no se leyeron datos válidos, retorna el último estado conocido

}

void Joystick::desconectar() {
    if (descriptorPuerto >= 0) {
        tcflush(descriptorPuerto, TCIFLUSH);
        
        //Cierra el descriptor del puerto
        close(descriptorPuerto);
        descriptorPuerto = -1;
        
        std::cout << "El Joystick ha sido desconectado" << std::endl;
    }
}