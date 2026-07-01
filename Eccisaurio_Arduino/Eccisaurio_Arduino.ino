

//pines
const int JOYSTICK_X_PIN = A0;//eje X del joystick
const int JOYSTICK_Y_PIN = A1;//Y del joystick

const int JOYSTICK_CENTER_X = 512;//Valor central del eje X
const int JOYSTICK_CENTER_Y = 512; //Valor central del eje Y
const int JOYSTICK_DEADZONE = 100;//zona muerta, evita lecturas inconsistentes

//ESTADOS DEL JOYSTICK
const char SALTAR = 'U';//hacia arriba
const char BAJAR = 'D';//hacia abajo
const char NEUTRO = 'N';

int joystickX = 0; // Lectura del eje X
int joystickY = 0;//Lectura del eje Y
char estadoActual = NEUTRO; // Estado actual del joystick
char estadoAnterior = NEUTRO; // Estado anterior para detectar cambios
unsigned long ultimaActualizacion = 0;
const unsigned long INTERVALO_ACTUALIZACION = 50; //Actualizar cada 50ms


void setup() {
    //Inicializa el puerto serial a 9600 baud (velocidad standard para Arduino)
    Serial.begin(9600);
    
    //Configura los pines del joystick como entradas
    pinMode(JOYSTICK_X_PIN, INPUT);
    pinMode(JOYSTICK_Y_PIN, INPUT);
        
    //Espera a que el puerto serial esté listo
    delay(1000);
    
}

char leerJoystick(){//Lee los valores analógicos del joystick y determina su estado
    joystickX = analogRead(JOYSTICK_X_PIN);
    joystickY = analogRead(JOYSTICK_Y_PIN);
    
    //Calcula la desviación del centro del joystick
    int desviaX = joystickX - JOYSTICK_CENTER_X;
    int desviaY = joystickY - JOYSTICK_CENTER_Y;
    
    //Si el joystick se mueve hacia arriba
    if (desviaY < -JOYSTICK_DEADZONE){
        return SALTAR; //Saltar
    }
    
    //Si el joystick se mueve significativamente hacia abajo
    if (desviaY > JOYSTICK_DEADZONE) {
        return BAJAR;
    }
    
    return NEUTRO;
}

void enviarEstadoSerial(char estado) {
    Serial.write(estado);
}

void loop() {
    //Verifica si es momento de actualizar(cada 50ms)
    unsigned long tiempoActual = millis();
    
    if (tiempoActual - ultimaActualizacion >= INTERVALO_ACTUALIZACION) {
        ultimaActualizacion = tiempoActual;
        
        //Lee el estado actual del joystick
        estadoActual = leerJoystick();
        
        //Envía el estado solo si este cambió
        if (estadoActual != estadoAnterior) {
            enviarEstadoSerial(estadoActual);
            estadoAnterior = estadoActual;
        }
    }
}
