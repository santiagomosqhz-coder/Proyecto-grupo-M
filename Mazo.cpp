#include "Mazo.h"
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

Mazo::Mazo() {
    crearMazo();
    barajar();
}
void Mazo::crearMazo() {
    cartas.clear();
    vector<Color> colores = { Color::Amarillo, Color::Azul, Color::Rojo, Color::Verde };
    for (Color c : colores) {
        for (int n = 1; n <= 9; n++) {
            cartas.push_back(Carta(n, c));
        }
    }
}
void Mazo::barajar() {
    unsigned seed = static_cast<unsigned>(time(nullptr));
    shuffle(cartas.begin(), cartas.end(), default_random_engine(seed));
}
