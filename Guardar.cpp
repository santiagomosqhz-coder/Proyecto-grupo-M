#include "Guardar.h"
#include "Juego.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>
#include <cstdlib>
#include <vector>

#ifdef _WIN32
    #include <direct.h>
    #define OBTENER_DIRECTORIO _getcwd
    const char SEPARADOR = '\\';
#else
    #include <unistd.h>
    #define OBTENER_DIRECTORIO getcwd
    const char SEPARADOR = '/';
#endif

using namespace std;

// ------------------------------------------------------------
// DONDE SE GUARDA / SE LEE EL ARCHIVO
// Con solo un nombre, se usa la "carpeta de trabajo": la carpeta
// desde la que ejecutas el programa. Al guardar, el programa
// muestra la ruta completa.
// Si prefieres una carpeta fija, escribe la ruta completa con "/", ej:
//   "C:/Users/USUARIO/Desktop/juego_cartas_proyecto/juego_cartas_proyecto/partida_guardada.txt"
// (la carpeta debe existir; el programa no la crea).
// ------------------------------------------------------------
static const string ARCHIVO_GUARDADO = "partida_guardada.txt";

// El mazo siempre tiene 4 colores x 9 numeros
static const int TOTAL_CARTAS = 36;

// ============================================================
// Utilidades internas
// ============================================================

// Lectura segura de un entero (no se queda en bucle infinito si no hay entrada)
static int leerOpcion(const string& mensaje, int minimo, int maximo) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            if (valor >= minimo && valor <= maximo) {
                return valor;
            }
            cout << "Opcion invalida. Debe estar entre " << minimo
                 << " y " << maximo << "." << endl;
        } else {
            if (cin.eof()) {
                cout << "\n[Error] No hay mas datos de entrada disponibles." << endl;
                exit(1);
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Debes escribir un numero." << endl;
        }
    }
}

// Devuelve la ruta completa donde quedo (o quedara) el archivo
static string rutaCompleta(const string& nombreArchivo) {
    bool esAbsoluta = nombreArchivo.find(':') != string::npos ||
                      (!nombreArchivo.empty() &&
                       (nombreArchivo[0] == '/' || nombreArchivo[0] == '\\'));
    if (esAbsoluta) {
        return nombreArchivo;
    }
    char carpeta[1024];
    if (OBTENER_DIRECTORIO(carpeta, sizeof(carpeta)) != nullptr) {
        return string(carpeta) + SEPARADOR + nombreArchivo;
    }
    return nombreArchivo;
}

// ============================================================
// Lectura del archivo de partida
// ============================================================

// Datos leidos del archivo, antes de aplicarlos al juego
struct DatosPartida {
    int numJugadores = 0;
    int idTurno = 0;
    vector<int> ids;
    vector<vector<Carta>> manos;
    vector<vector<Carta>> ganadas;
};

static string recortar(const string& s) {
    size_t ini = s.find_first_not_of(" \t\r\n");
    if (ini == string::npos) return "";
    size_t fin = s.find_last_not_of(" \t\r\n");
    return s.substr(ini, fin - ini + 1);
}

static bool textoAColor(const string& texto, Color& color) {
    if (texto == "Amarillo") { color = Color::Amarillo; return true; }
    if (texto == "Azul")     { color = Color::Azul;     return true; }
    if (texto == "Rojo")     { color = Color::Rojo;     return true; }
    if (texto == "Verde")    { color = Color::Verde;    return true; }
    return false;
}

// Lee el entero que aparece en 'linea' a partir de la posicion 'desde'
static bool enteroDesde(const string& linea, size_t desde, int& valor) {
    if (desde >= linea.size()) return false;
    istringstream ss(linea.substr(desde));
    return static_cast<bool>(ss >> valor);
}

// Lee las cartas con formato "[Color N]" que aparecen despues de los ':'
static bool leerCartas(const string& linea, vector<Carta>& destino) {
    size_t pos = linea.find(':');
    if (pos == string::npos) return false;

    while (true) {
        pos = linea.find('[', pos);
        if (pos == string::npos) break;
        size_t fin = linea.find(']', pos);
        if (fin == string::npos) return false;

        istringstream ss(linea.substr(pos + 1, fin - pos - 1));
        string textoColor;
        int numero;
        Color color;
        if (!(ss >> textoColor >> numero)) return false;
        if (!textoAColor(textoColor, color)) return false;
        if (numero < 1 || numero > 9) return false;

        destino.push_back(Carta(numero, color));
        pos = fin + 1;
    }
    return true;
}

// Comprueba que los datos leidos tengan sentido
static bool validar(const DatosPartida& d) {
    int n = d.numJugadores;
    if (n < 2 || n > 4) return false;
    if (static_cast<int>(d.ids.size()) != n) return false;
    for (int i = 0; i < n; i++) {
        if (d.ids[i] != i + 1) return false;
    }
    if (d.idTurno < 1 || d.idTurno > n) return false;

    // Ninguna carta puede aparecer dos veces
    bool usada[4][10] = {};
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < 2; k++) {
            const vector<Carta>& cartas = (k == 0) ? d.manos[i] : d.ganadas[i];
            for (const Carta& c : cartas) {
                bool& marca = usada[static_cast<int>(c.getColor())][c.getNumero()];
                if (marca) return false;
                marca = true;
            }
        }
    }
    return true;
}

static bool leerArchivo(const string& nombre, DatosPartida& d) {
    ifstream archivo(nombre);
    if (!archivo.is_open()) return false;

    bool cabecera = false;
    string cruda;
    while (getline(archivo, cruda)) {
        string linea = recortar(cruda);
        if (linea.empty()) continue;

        if (linea == "===== PARTIDA GUARDADA =====") {
            cabecera = true;
        } else if (linea.rfind("Numero de jugadores:", 0) == 0) {
            if (!enteroDesde(linea, linea.find(':') + 1, d.numJugadores)) return false;
        } else if (linea.rfind("Turno del jugador:", 0) == 0) {
            if (!enteroDesde(linea, linea.find(':') + 1, d.idTurno)) return false;
        } else if (linea.rfind("Jugador ", 0) == 0) {
            int id;
            if (!enteroDesde(linea, 8, id)) return false;
            d.ids.push_back(id);
            d.manos.push_back(vector<Carta>());
            d.ganadas.push_back(vector<Carta>());
        } else if (linea.rfind("Mano (", 0) == 0) {
            if (d.manos.empty() || !leerCartas(linea, d.manos.back())) return false;
        } else if (linea.rfind("Cartas ganadas (", 0) == 0) {
            if (d.ganadas.empty() || !leerCartas(linea, d.ganadas.back())) return false;
        }
    }

    return cabecera && validar(d);
}

// Aplica los datos a un Juego recien creado, usando solo metodos publicos:
//  - obtenerJugador(), recibirCarta() y agregarCartaGanada() para cartas
//  - cambiarTurno() para dejar el turno donde estaba
static void aplicarEstado(Juego& juego, const DatosPartida& d) {
    for (int i = 0; i < d.numJugadores; i++) {
        Jugador& j = juego.obtenerJugador(d.ids[i]);
        for (const Carta& c : d.manos[i])   j.recibirCarta(c);
        for (const Carta& c : d.ganadas[i]) j.agregarCartaGanada(c);
    }
    while (juego.getJugadores()[juego.getTurno()].getId() != d.idTurno) {
        juego.cambiarTurno();
    }
}

// ============================================================
// Guardar
// ============================================================

void Guardar::ofrecerGuardado(const Juego& juego) {
    cout << "\n----- Fin del turno -----" << endl;
    cout << "1. Seguir jugando" << endl;
    cout << "2. Guardar la partida" << endl;

    int opcion = leerOpcion("Elige una opcion (1-2): ", 1, 2);

    if (opcion == 2) {
        if (guardarPartida(juego, ARCHIVO_GUARDADO)) {
            cout << "Partida guardada en: " << rutaCompleta(ARCHIVO_GUARDADO) << endl;
            cout << "\n----- Contenido guardado -----" << endl;
            escribirPartida(juego, cout);
            cout << "------------------------------" << endl;
        } else {
            cout << "[Error] No se pudo crear el archivo: "
                 << rutaCompleta(ARCHIVO_GUARDADO) << endl;
        }
    }
}

bool Guardar::guardarPartida(const Juego& juego, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        return false;
    }
    escribirPartida(juego, archivo);
    archivo.close();
    return true;
}

void Guardar::escribirPartida(const Juego& juego, ostream& salida) {
    const vector<Jugador>& jugadores = juego.getJugadores();

    salida << "===== PARTIDA GUARDADA =====" << endl;
    salida << "Numero de jugadores: " << juego.getNumJugadores() << endl;
    salida << "Turno del jugador: " << jugadores[juego.getTurno()].getId() << endl;
    salida << "Ultimo color elegido: " << colorToString(juego.getColorElegido()) << endl;
    salida << "Ultimo criterio: " << criterioToString(juego.getCriterio()) << endl;

    int cartasEnJuego = 0; // en manos + ganadas

    salida << "\n--- Jugadores ---" << endl;
    for (const Jugador& j : jugadores) {
        salida << "\nJugador " << j.getId() << endl;

        salida << "  Mano (" << j.getMano().size() << "): ";
        for (const Carta& c : j.getMano()) {
            salida << "[" << colorToString(c.getColor()) << " " << c.getNumero() << "] ";
        }
        salida << endl;

        salida << "  Cartas ganadas (" << j.getPuntos() << "): ";
        for (const Carta& c : j.getCartasGanadas()) {
            salida << "[" << colorToString(c.getColor()) << " " << c.getNumero() << "] ";
        }
        salida << endl;

        cartasEnJuego += static_cast<int>(j.getMano().size()) + j.getPuntos();
    }

    // Cartas que siguen en el mazo = total - las que ya estan en manos o ganadas.
    // Se calcula asi (y no con getMazo()) para que sea correcto tambien
    // en una partida que fue cargada desde un archivo.
    salida << "\n--- Mazo ---" << endl;
    salida << "Cartas restantes: " << (TOTAL_CARTAS - cartasEnJuego) << endl;
}

// Continua una partida ya cargada. Es el mismo bucle de Juego::iniciarJuego(),
// pero sin repartir cartas de nuevo (iniciarJuego() siempre reparte).
void Guardar::reanudarPartida(Juego& juego) {
    while (!juego.haTerminado()) {
        juego.iniciarRonda();
        juego.jugarRonda();
        juego.cambiarTurno();

        if (!juego.haTerminado()) {
            ofrecerGuardado(juego);
        }
    }

    int ganador = juego.determinarGanadorJuego();
    cout << "\n=== FIN DEL JUEGO ===" << endl;
    cout << "El jugador " << ganador << " gana la partida con "
         << juego.obtenerJugador(ganador).getPuntos() << " cartas acumuladas." << endl;
}

bool Guardar::ofrecerCargar() {
    // Si el archivo no existe, no hay nada que ofrecer
    ifstream existe(ARCHIVO_GUARDADO);
    if (!existe.is_open()) {
        return false;
    }
    existe.close();

    cout << "\nSe encontro una partida guardada: " << rutaCompleta(ARCHIVO_GUARDADO) << endl;
    cout << "1. Nueva partida" << endl;
    cout << "2. Continuar la partida guardada" << endl;
    int opcion = leerOpcion("Elige una opcion (1-2): ", 1, 2);

    if (opcion == 1) {
        return false;
    }

    DatosPartida datos;
    if (!leerArchivo(ARCHIVO_GUARDADO, datos)) {
        cout << "[Error] El archivo esta danado o no tiene el formato esperado. "
             << "Se iniciara una partida nueva.\n" << endl;
        return false;
    }

    Juego juego(datos.numJugadores);
    aplicarEstado(juego, datos);

    cout << "\n=== Partida cargada: " << datos.numJugadores << " jugadores, "
         << "turno del jugador " << datos.idTurno << " ===" << endl;

    reanudarPartida(juego);
    return true;
}
