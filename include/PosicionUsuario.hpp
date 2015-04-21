#ifndef PosicionUsuario_HPP
#define	PosicionUsuario_HPP

#include "Posicion.hpp"
#include "json/json.h"
#include <string> 

#include <iostream>

class PosicionUsuario : public Posicion {
    private:
        int usuario_id;
        const std::string nombreClase="posUsuario";
    	
   
    public:
    PosicionUsuario(double* lat,double* lon ,int* id ); 
    PosicionUsuario(std::string*); // Cosntructor a partir de un documento Json en formato string
    // PosicionUsuario();
    void getPosicionUsuarioJson(std::string*);
    bool setPosicionUsuarioJson(Json::Value*);
    bool jsonToPosicionUsuario(Json::Value*);
    bool actualizarPosicion(PosicionUsuario* posActualizar);

    double getLatitud();
    double getLongitud();
    int getIdUsuario();
    	
    };

#endif	/* PosicionUsuario_HPP */