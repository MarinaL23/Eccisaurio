# VIDEOJUEGO RETRO INSPIRADO EN CHROME DINO: ECCISAURIO



## Descripción general
**EcciSaurio** es un videojuego de corredor infinito en 2D inspirado en el popular juego Chrome Dino. El jugador controla un dinosaurio que corre automáticamente a través de un escenario desértico y debe evitar obstáculos como cactus y pterodáctilos mediante acciones de salto y agacharse. Conforme avanza la partida, la velocidad del juego aumenta progresivamente, incrementando el nivel de dificultad y el desafío para alcanzar la mayor puntuación posible.

Esta versión incorpora características adicionales respecto al juego original, incluyendo un sistema de vidas, power-ups especiales y una integración con hardware mediante Arduino. El jugador dispone de tres vidas antes de perder la partida y puede obtener ventajas temporales como doble puntuación, protección contra obstáculos o vidas extra.

La lógica principal del videojuego se desarrolla en C++, la interfaz gráfica se implementa con Raylib, los controles físicos se gestionan mediante Arduino UNO con botones dedicados para saltar y agacharse, y ciertas funciones críticas como el cálculo de puntuación, control de vidas y velocidad se implementan en lenguaje ensamblador NASM.



## Instrucciones de compilación
Para esta segunda iteración únicamente se está utilizando C++, por lo que el proyecto puede compilarse ejecutando el siguiente comando desde la carpeta raíz de EcciSaurio:

`g++ main.cpp Juego.cpp -o Eccisaurio -lraylib`


## Instrucciones de ejecución
Una vez compilado el proyecto, ejecute el siguiente comando desde la carpeta raíz de EcciSaurio:


`./Eccisaurio`

Al iniciar el programa se abrirá una ventana con el menú principal del juego. Para comenzar una partida, presione la tecla Enter o haga clic sobre el botón Play.

## Controles
- **Barra espaciadora o flecha hacia arriba:** saltar.
- **Enter:** iniciar el juego desde el menú principal.




## Dependencias necesarias
Para compilar y ejecutar EcciSaurio es necesario tener instalada la biblioteca Raylib, la cual se utiliza para la creación de la ventana, renderizado de gráficos, manejo de texturas y procesamiento de entradas del usuario.



## Miembros
* Andrea Cabello Mendez - C4D467  
* Daniel Rodríguez Ruiz - C4J199
* Marina Liang Liu - C4G502


