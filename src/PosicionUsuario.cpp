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

void PosicionUsuario::getPosicionUsuarioJson(std::string* posJson)
{
	Json::Value root;   // starts as "null"; will contain the root value after parsing
    Json::FastWriter writer;
    root["IdObjecto"] = "posUsuario";
    root["IdUsuario"] = usuario_id;
    root["longitud"] = longitud;
    root["latitud"] = latitud;

    *posJson = writer.write(root);
}

/*PosicionJugador::~PosicionJugador() {
}*/

