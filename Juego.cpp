#include "Juego.h"
#include <iostream>

using namespace std;

Juego::Juego(int numJugadores)
    : numJugadores(numJugadores), turno(0), numCartasIniciales(5),
      colorElegido(Color::Amarillo), criterio(Criterio::Mayor) {
    for (int i = 0; i < numJugadores; i++) {
        jugadores.push_back(Jugador(i + 1));
    }
}

void Juego::iniciarJuego() {
    cout << "=== Iniciando juego con " << numJugadores << " jugadores ===" << endl;
    repartirCartas();

    while (!haTerminado()) {
        iniciarRonda();
        jugarRonda();
        cambiarTurno();
    }

    int ganador = determinarGanadorJuego();
    cout << "\n=== FIN DEL JUEGO ===" << endl;
    cout << "El jugador " << ganador << " gana la partida con "
         << obtenerJugador(ganador).getPuntos() << " cartas acumuladas." << endl;
}

void Juego::repartirCartas() {
    for (int v = 0; v < numCartasIniciales; v++) {
        for (Jugador& j : jugadores) {
            if (!mazo.estaVacio()) {
                j.recibirCarta(mazo.repartirCarta());
            }
        }
    }
    cout << "Se repartieron " << numCartasIniciales << " cartas a cada jugador." << endl;
}

void Juego::iniciarRonda() {
    cout << "\n----- Turno del jugador " << jugadores[turno].getId() << " -----" << endl;

    // El jugador con el turno elige color y criterio
    int opcionColor;
    cout << "Elige color (0=Amarillo, 1=Azul, 2=Rojo, 3=Verde): ";
    cin >> opcionColor;
    while (opcionColor < 0 || opcionColor > 3) {
        cout << "Opcion invalida. Elige color (0-3): ";
        cin >> opcionColor;
    }
    colorElegido = static_cast<Color>(opcionColor);

    int opcionCriterio;
    cout << "Elige criterio (0=Mayor, 1=Menor): ";
    cin >> opcionCriterio;
    while (opcionCriterio < 0 || opcionCriterio > 1) {
        cout << "Opcion invalida. Elige criterio (0-1): ";
        cin >> opcionCriterio;
    }
    criterio = static_cast<Criterio>(opcionCriterio);

    cout << "Color elegido: " << colorToString(colorElegido)
         << " | Criterio: " << criterioToString(criterio) << endl;
}

void Juego::jugarRonda() {
    vector<pair<int, Carta>> cartasJugadas; // idJugador, carta

    for (Jugador& j : jugadores) {
        if (j.getNumeroCartas() == 0) continue;

        j.mostrarMano();
        int posicion;
        cout << "Jugador " << j.getId() << ", elige la posicion de la carta a jugar: ";
        cin >> posicion;
        while (posicion < 0 || posicion >= j.getNumeroCartas()) {
            cout << "Posicion invalida. Intenta de nuevo: ";
            cin >> posicion;
        }

        Carta jugada = j.jugarCarta(posicion);
        cout << "Jugador " << j.getId() << " jugo: ";
        jugada.mostrar();
        cout << endl;

        cartasJugadas.push_back(make_pair(j.getId(), jugada));
    }

    int idGanador = determinarGanadorRonda(cartasJugadas);
    cout << "El jugador " << idGanador << " gana la ronda." << endl;

    // El ganador se lleva todas las cartas jugadas (incluida la propia)
    Jugador& ganador = obtenerJugador(idGanador);
    for (auto& par : cartasJugadas) {
        ganador.agregarCartaGanada(par.second);
    }
}

int Juego::determinarGanadorRonda(vector<pair<int, Carta>>& cartasJugadas) {
    vector<pair<int, Carta>> candidatas;

    // Primero se buscan las cartas que coinciden con el color elegido
    for (auto& par : cartasJugadas) {
        if (par.second.getColor() == colorElegido) {
            candidatas.push_back(par);
        }
    }

    // Si nadie jugo el color elegido, se comparan todas las cartas jugadas
    if (candidatas.empty()) {
        candidatas = cartasJugadas;
    }

    int idGanador = candidatas[0].first;
    int valorGanador = candidatas[0].second.getNumero();

    for (auto& par : candidatas) {
        int valor = par.second.getNumero();
        if (criterio == Criterio::Mayor) {
            if (valor > valorGanador) {
                valorGanador = valor;
                idGanador = par.first;
            }
        } else { // Menor
            if (valor < valorGanador) {
                valorGanador = valor;
                idGanador = par.first;
            }
        }
    }

    return idGanador;
}

void Juego::cambiarTurno() {
    turno = (turno + 1) % numJugadores;
}

int Juego::determinarGanadorJuego() {
    int idGanador = jugadores[0].getId();
    int maxPuntos = jugadores[0].getPuntos();

    for (Jugador& j : jugadores) {
        if (j.getPuntos() > maxPuntos) {
            maxPuntos = j.getPuntos();
            idGanador = j.getId();
        }
    }
    return idGanador;
}

Jugador& Juego::obtenerJugador(int id) {
    for (Jugador& j : jugadores) {
        if (j.getId() == id) return j;
    }
    return jugadores[0];
}

bool Juego::haTerminado() {
    for (Jugador& j : jugadores) {
        if (j.getNumeroCartas() > 0) return false;
    }
    return true;
}
