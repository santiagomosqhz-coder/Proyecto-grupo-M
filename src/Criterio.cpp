#include "Criterio.h"

std::string criterioToString(Criterio c) {
    return c == Criterio::Mayor ? "Mayor" : "Menor";
}
