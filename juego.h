#ifndef JUEGO_H
#define JUEGO_H

#include <vector>
#include <utility>
#include "Color.h"
#include "Criterio.h"
#include "Carta.h"
#include "Mazo.h"
#include "Jugador.h"

// ============================================================
// Clase Juego
// Relaciones del diagrama:
//   Juego "tiene" Jugador  (composicion/agregacion 1..*)
//   Juego "usa" Mazo
// ============================================================
class Juego {
private:
    int numJugadores;
    int turno;
    int numCartasIniciales;
    std::vector<Jugador> jugadores;
    Mazo mazo;
    Color colorElegido;
    Criterio criterio;

public:
    Juego(int numJugadores);

    void iniciarJuego();
    void repartirCartas();
    void iniciarRonda();
    void jugarRonda();
    int determinarGanadorRonda(std::vector<std::pair<int, Carta>>& cartasJugadas);
    void cambiarTurno();
    int determinarGanadorJuego();

    Jugador& obtenerJugador(int id);
    bool haTerminado();
};

#endif // JUEGO_H