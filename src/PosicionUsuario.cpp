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

// Retorna la posición en formato Json
void PosicionUsuario::getPosicionUsuarioJson(std::string* posJson)
{
	Json::Value root; // Objeto que almacena la estructura Json
    Json::FastWriter writer; //Conversor de Objeto Json a String Json

    // En el objeto json se crean campos "clave":"valor"
    root["idUsuario"] = usuario_id;
    root["longitud"] = longitud;
    root["latitud"] = latitud;

    // Se convierte el Objeto Json a formato String
    *posJson = writer.write(root);
}

// Actualiza la posición 
bool PosicionUsuario::actualizarPosicion(PosicionUsuario* posActualizar){
    longitud = posActualizar->getLongitud();
    latitud = posActualizar->getLatitud();
    return true;
}

int PosicionUsuario::getIdUsuario(){
    return usuario_id;
}

double PosicionUsuario::getLatitud(){
    return latitud;
}

double PosicionUsuario::getLongitud(){
    return longitud;
}


/*PosicionJugador::~PosicionJugador() {
}*/

