#include "Carta.h"
#include <iostream>
using namespace std;

Carta::Carta(int numero, Color color)
    : numero(numero), color(color), visible(true) {}

int Carta::getNumero() const {
    return numero;
}