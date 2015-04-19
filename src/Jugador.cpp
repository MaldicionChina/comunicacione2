#include "Jugador.hpp"

Jugador::Jugador(int* idJugadorCons,std::string* nicknameCons,
      int* lvlJugador, int* vida, int*vidaMax,double* lon, double* lati){
        
        idJugador = *idJugadorCons; 
        nickname = *nicknameCons; 
        nivelJudador = *lvlJugador; 
        vidaJudador = *vida; 
        vidaMaxUsuario = *vidaMax; 
        longitud = *lon; 
        latitud = *lati; 
        
    } // Constructor
    
int Jugador::getIdJugador(){
        return idJugador;
    }