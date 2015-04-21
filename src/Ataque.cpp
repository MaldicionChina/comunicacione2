#include "Ataque.hpp"

Ataque::Ataque(int atacante, int atacado){//atado es atacado atante es atacante
        _atacante = atacante;
        _atacado = atacado;
} // Constructor

int Ataque::getIdAtacante(){
	return _atacante;
}
int Ataque::getIdAtacado(){
	return _atacado;
}

bool Ataque::ataqueToJson(std::string* ataque){
	Json::Value atac;  // Objeto Json 
    Json::FastWriter writer; // Conversor de objeto Json a formato string 

    atac["atacante"] = _atacante; 
    atac["atacado"] = _atacado;

    *ataque = writer.write(atac);

	return true;
}
    
Ataque::Ataque(std::string* ataque){

	Json::Reader readerJson; // Conversor de string Json a Objeto Json
    Json::Value usuario; // Objeto contenedor del documento Json

    // Se realiza la conversión del archivo Json a Objeto 
    if(!readerJson.parse(*ataque,usuario)) // Se verifica que se realice correctamente la conversion
    {
        std::cout  << "Error en la conversión de documento Json a Objeto Json\n"
       << readerJson.getFormattedErrorMessages();
    }

    // Se obtiene el valor de cada campo de acuerdo a la clave, en caso de no encontrarse retorna "Not found"
    _atacado = std::stoi(usuario.get("atacado", "NULL" ).asString()); 
    _atacante = std::stoi(usuario.get("atacante", "NULL" ).asString()); 

}