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
Carta Jugador::jugarCarta(int posicion) {
    Carta jugada = mano[posicion];
    mano.erase(mano.begin() + posicion);
    return jugada;
}

void Jugador::agregarCartaGanada(Carta carta) {
    cartasGanadas.push_back(carta);
}
int Jugador::getNumeroCartas() const {
    return static_cast<int>(mano.size());
}

int Jugador::getPuntos() const {
    return static_cast<int>(cartasGanadas.size());
}
void Jugador::mostrarMano() const {
    cout << "Jugador " << idJugador << " - mano: ";
    for (size_t i = 0; i < mano.size(); i++) {
        cout << "(" << i << ") ";
        cout << "[" << colorToString(mano[i].getColor()) << " " << mano[i].getNumero() << "] ";
    }
    cout << endl;
}