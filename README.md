# Proyecto Grupo M - Juego de Cartas

Juego de cartas por turnos desarrollado en **C++**. Cada jugador recibe cinco cartas y compite ronda a ronda intentando jugar la carta más alta o más baja, según lo que indique el jugador que abre la ronda.





## Contenido

- [Descripción del juego](#descripción-del-juego)
- [Reglas](#reglas)
- [Desarrollo de una ronda](#desarrollo-de-una-ronda)
- [Fin del juego](#fin-del-juego)
- [Diagrama UML](#diagrama-uml)
- [Estructura del proyecto](#estructura-del-proyecto)
- [Compilación y ejecución](#compilación-y-ejecución)
- [Integrantes](#integrantes)

## Descripción del juego

El mazo tiene cartas de **4 colores**: amarillo, azul, rojo y verde. Cada color tiene los números del **1 al 9**, para un total de 36 cartas.

## Reglas

1. Se reparten **5 cartas por jugador**.
2. Un jugador abre la ronda y coloca una carta **boca abajo**, de modo que los demás no la vean.
3. Ese jugador anuncia en voz alta el **color** de su carta y si el criterio de la ronda es el número **más alto** o el **más bajo**.
4. Los demás jugadores responden con la carta que consideren más adecuada según el criterio anunciado.
5. Se revelan todas las cartas. **Gana la ronda** quien tenga la carta con el número más bajo o más alto, según el criterio.
6. El juego continúa ronda tras ronda.

## Desarrollo de una ronda

| Paso | Acción |
|------|--------|
| 1 | El jugador que abre coloca una carta boca abajo. |
| 2 | Anuncia el color y el criterio (más alto o más bajo). |
| 3 | Los demás jugadores juegan una carta. |
| 4 | Se revelan las cartas y se determina al ganador de la ronda. |
| 5 | Se actualizan los puntos y comienza una nueva ronda. |

## Fin del juego

Los puntos se suman de acuerdo con la cantidad de cartas. El juego continúa hasta que un jugador se queda **sin cartas**; ese jugador es quien pierde, y gana quien tenga más puntos.
