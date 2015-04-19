/* 
 * File:   PosicionJugador.cpp
 * Author: emmanuel
 * 
 * Created on 18 de abril de 2015, 09:42 PM
 */

#include "PosicionUsuario.hpp"

PosicionUsuario::PosicionUsuario(double* lat,double* lon ,int* id ) {//Contructor lat es latitud lon longitud id es idusuario
    latitud = *lat;
    longitud = *lon;
    usuario_id = *id;
}

PosicionUsuario::PosicionUsuario(const PosicionUsuario& orig) {
}

/*PosicionJugador::~PosicionJugador() {
}*/

