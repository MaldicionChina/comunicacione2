#include "Usuario.hpp"

Usuario::Usuario(int* idUsuarioCons,std::string* nicknameCons,
      int* lvlUsuario, int* vida, int*vidaMax,double* lon, double* lati){
        
        idUsuario = *idUsuarioCons; 
        nickname = *nicknameCons; 
        nivelUsuario = *lvlUsuario; 
        vidaUsuario = *vida; 
        vidaMaxUsuario = *vidaMax; 
        longitud = *lon; 
        latitud = *lati; 
        
    } // Constructor
    
int Usuario::getIdUsuario(){
        return idUsuario;
    }