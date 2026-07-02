CXX = g++
NASM = nasm
CXXFLAGS = -std=c++17
LIBS = -lraylib -lX11 -lm

SOURCES = main.cpp Juego.cpp Joystick.cpp
OBJECTS = Funciones.o
TARGET = Eccisaurio

all: $(TARGET)

#Compilar ejecutable
$(TARGET): $(SOURCES) $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(SOURCES) $(OBJECTS) -o $(TARGET) $(LIBS)

#Compilar ensamblador
Funciones.o: Funciones.asm
	$(NASM) -f elf64 Funciones.asm -o Funciones.o

#Ejecutar
run: $(TARGET)
	./$(TARGET)

#Limpiar archivos compilados
clean:
	rm -f $(OBJECTS) $(TARGET)

rebuild: clean all

.PHONY: all run clean rebuild