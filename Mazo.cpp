#include "Mazo.h"
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

Mazo::Mazo() {
    crearMazo();
    barajar();
}
