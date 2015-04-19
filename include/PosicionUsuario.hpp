#ifndef PosicionUsuario_HPP
#define	PosicionUsuario_HPP

#include "Posicion.hpp"
#include "json/json.h"
#include <string> 

#include <iostream>

class PosicionUsuario : public Posicion {
    private:
        int usuario_id;
    	
   
    public:
    PosicionUsuario(double* lat,double* lon ,int* id ); 
    // PosicionUsuario();
    void getPosicionUsuarioJson(std::string*);

    bool setPosicionUsuarioJson(Json::Value*);
    	
    };

#endif	/* PosicionUsuario_HPP */