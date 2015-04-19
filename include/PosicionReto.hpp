/* 
 * File:   PosicionReto.hpp
 * Author: emmanuel
 *
 */

#ifndef POSICIONRETO_HPP
#define	POSICIONRETO_HPP
#include "Posicion.hpp"

class PosicionReto : public Posicion {
public:
    PosicionReto();// Contructor
    PosicionReto(const PosicionReto& orig);
    virtual ~PosicionReto();
private:
    int reto_id; //Identificacion del reto
    
    

};

#endif	/* POSICIONRETO_HPP */

