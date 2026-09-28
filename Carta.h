#ifndef CARTA_H
#define CARTA_H

#include "Color.h"

// ============================================================
// Clase Carta
// ============================================================
class Carta {
private:
    int numero;
    Color color;
    bool visible;

public:
    Carta(int numero = 0, Color color = Color::Amarillo);

    int getNumero() const;
    Color getColor() const;

    void mostrar();
    void ocultar();

    bool esVisible() const;
};

#endif // CARTA_H
