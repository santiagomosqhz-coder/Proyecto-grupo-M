#ifndef GUARDAR_H
#define GUARDAR_H

#include <string>
#include <ostream>

// Declaracion adelantada: evita incluir Juego.h aqui y asi no hay
// dependencia circular (Juego.cpp incluye Guardar.h y Guardar.cpp incluye Juego.h).
class Juego;

// ============================================================
// Clase Guardar
// - Ofrece guardar la partida despues de cada turno.
// - Ofrece continuar una partida guardada al iniciar el programa.
// ============================================================
class Guardar {
public:
    // Pregunta: 1 = seguir jugando, 2 = guardar la partida.
    static void ofrecerGuardado(const Juego& juego);

    // Escribe el estado del juego en un archivo de texto.
    // Devuelve true si el archivo se pudo crear/escribir.
    static bool guardarPartida(const Juego& juego, const std::string& nombreArchivo);

    // Si existe una partida guardada, pregunta si se quiere continuar.
    // Devuelve true si cargo la partida y la jugo hasta el final
    // (en ese caso main debe terminar). Devuelve false si no hay partida
    // guardada, si el usuario prefiere una nueva o si el archivo es invalido.
    static bool ofrecerCargar();

private:
    static void escribirPartida(const Juego& juego, std::ostream& salida);
    static void reanudarPartida(Juego& juego);
};

#endif // GUARDAR_H
