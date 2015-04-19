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

PosicionUsuario::PosicionUsuario(std::string* rpl){
    Json::Reader readerJson;
    Json::Value posicion;
    // Se realiza la conversión del archivo Json a Objeto 
    if(!readerJson.parse(*rpl,posicion)) // Se verifica que se realice correctamente la conversion
    {
        std::cout  << "Error en la conversión de documento Json a Objeto Json\n"
       << readerJson.getFormattedErrorMessages();
    }

    // Se obtiene el valor de cada par "clave":"valor", se convierte a string y luego al correspondiente
    // tipo de dato
    latitud =  std::stod(posicion.get("latitud", "Not Found" ).asString()); 
    longitud = std::stod(posicion.get("longitud", "Not Found" ).asString());
    usuario_id = std::stoi(posicion.get("idUsuario", "Not Found" ).asString());

}

void PosicionUsuario::getPosicionUsuarioJson(std::string* posJson)
{
	Json::Value root;   // starts as "null"; will contain the root value after parsing
    Json::FastWriter writer; 
    root["IdObjecto"] = nombreClase;
    root["idUsuario"] = usuario_id;
    root["longitud"] = longitud;
    root["latitud"] = latitud;

    *posJson = writer.write(root);
}
bool PosicionUsuario::jsonToPosicionUsuario(Json::Value*){

}

double PosicionUsuario::getLatitud(){
    return latitud;
}

double PosicionUsuario::getLongitud(){
    return longitud;
}


/*PosicionJugador::~PosicionJugador() {
}*/

