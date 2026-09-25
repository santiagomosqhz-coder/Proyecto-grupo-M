#ifndef JUGADOR_H
#define JUGADOR_H

#include <vector>
#include "Carta.h"
class jugador {

    int idJugador;
    std::vector<Carta> mano;
    std::vector<Carta> cartasGanadas;

public:
    Jugador(int idJugador = 0);


}