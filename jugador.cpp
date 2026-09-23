class Jugador {
private:
    int idJugador;
    vector<Carta> mano;
    vector<Carta> cartasGanadas;

    public:
    Jugador(int idJugador = 0) : idJugador(idJugador) {
        
    }

    int getId() const {
        return idJugador; 
        
    }

    void recibirCarta(Carta carta) {
        mano.push_back(carta);
    }

    Carta jugarCarta(int posicion) {
        Carta jugada = mano[posicion];
        mano.erase(mano.begin() + posicion);
        return jugada;
    }    

};