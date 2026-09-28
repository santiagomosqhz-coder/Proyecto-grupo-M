#include "Color.h"

std::string colorToString(Color c) {
    switch (c) {
        case Color::Amarillo: return "Amarillo";
        case Color::Azul:     return "Azul";
        case Color::Rojo:     return "Rojo";
        case Color::Verde:    return "Verde";
    }
    return "Desconocido";
}