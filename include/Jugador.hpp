
#ifndef JUGADOR_HPP
#define	JUGADOR_HPP

#include <iostream>

class Jugador{
private:
    int idJugador; // ID único que identifica inequivocamente al Jugador en todo el juego
    std::string nickname; // Nombre en el juego para el Jugador
    int nivelJudador; // Nivel en el juego del Jugador
    int vidaJudador; // Vida actual de usuario 
    int vidaMaxUsuario; // Vida total que puede tener el usuario; varia de acuerdo al nivel
    double longitud; // Dato correspondiente e la longitud de la pocisión del usuario
    double latitud; // Dato correspondiente e la latitud de la pocisión del usuario
    
public:
    Jugador(int* idJugadorCons,std::string* nicknameCons,
      int* lvlJugador, int* vida, int*vidaMax,double* lon, double* lati); // Constructor    
    
    int getIdJugador(); // Obtener el id del jugador
};


#endif	/* JUGADOR_HPP */

