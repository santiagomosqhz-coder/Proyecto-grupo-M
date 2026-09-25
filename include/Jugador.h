#ifndef JUGADOR_H
#define JUGADOR_H

#include <vector>
#include "Carta.h"
class Jugador {
private:
    int idJugador;
    std::vector<Carta> mano;
    std::vector<Carta> cartasGanadas;
public:
    Jugador(int idJugador = 0);

    int getId() const;

    void recibirCarta(Carta carta);
    Carta jugarCarta(int posicion);
    void agregarCartaGanada(Carta carta);

    int getNumeroCartas() const;
    int getPuntos() const;

    void mostrarMano() const;
    bool tieneCartasDeColor(Color color) const;    

};
#endif