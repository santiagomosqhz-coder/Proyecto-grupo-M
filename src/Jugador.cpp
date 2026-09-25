#include "Jugador.h"
#include <iostream>
using namespace std;

Jugador::Jugador(int idJugador) : idJugador(idJugador) {}
int Jugador::getId() const {
    return idJugador;
}

void Jugador::recibirCarta(Carta carta) {
    mano.push_back(carta);
}
