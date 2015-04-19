/* 
 * File:   PosicionReto.cpp
 * Author: emmanuel
 * 
 * Created on 18 de abril de 2015, 09:47 PM
 */


#include "PosicionReto.hpp"

PosicionReto::PosicionReto(double* lat,double* lon ,int* id) {
    latitud = *lat;
    longitud = *lon;
    reto_id = *id;
}

PosicionReto::PosicionReto(const PosicionReto& orig) {
}

PosicionReto::~PosicionReto() {
}

