#include <iostream>
#include "Juego.h"

using namespace std;

int main() {
    int numJugadores;
    cout << "===== JUEGO DE CARTAS POR COLOR Y VALOR =====" << endl;
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
