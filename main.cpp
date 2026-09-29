#include <iostream>
#include "Juego.h"
#include "Guardar.h"

using namespace std;

int main() {
    int numJugadores;
    cout << "===== JUEGO DE CARTAS POR COLOR Y VALOR =====" << endl;
    
    // Si hay una partida guardada, se ofrece continuarla
    if (Guardar::ofrecerCargar()) {
        return 0;   // la partida cargada ya se jugo hasta el final
    }
    cout << "Numero de jugadores: ";
    cin >> numJugadores;
    while (numJugadores < 2 || numJugadores > 4) {
        cout << "El numero de jugadores debe ser entre 2 y 4 (36 cartas en total). Intenta de nuevo: ";
        cin >> numJugadores;
    }

    Juego juego(numJugadores);
    juego.iniciarJuego();

    return 0;
}
