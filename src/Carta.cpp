#include "Carta.h"
#include <iostream>
using namespace std;

Carta::Carta(int numero, Color color)
    : numero(numero), color(color), visible(true) {}

int Carta::getNumero() const {
    return numero;
}
Color Carta::getColor() const {
    return color;
}
void Carta::mostrar() {
    visible = true;
    cout << "[" << colorToString(color) << " " << numero << "]";
}

void Carta::ocultar() {
    visible = false;
}

bool Carta::esVisible() const {
    return visible;
}