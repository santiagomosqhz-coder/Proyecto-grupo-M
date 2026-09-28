#ifndef MAZO_H
#define MAZO_H

#include <vector>
#include "Carta.h"
class Mazo {
private:
    std::vector<Carta> cartas;

public:
    Mazo();
    
    void crearMazo();
    void barajar();
    Carta repartirCarta();
    bool estaVacio() const;

    int getNumeroCartas() const;
};

#endif // MAZO_H
