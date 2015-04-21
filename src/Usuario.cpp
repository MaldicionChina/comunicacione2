#include "Usuario.hpp"

  
int Usuario::getIdUsuario(){
        return idUsuario;
    }

std::string Usuario::getNickName(){
        return nickName;
}

//Actualiza posición del objeto posUsuario
bool Usuario::actualizarPos(PosicionUsuario* posActualizar){
        posUsuario->actualizarPosicion(posActualizar);
        return true;
}

// Obtiene latitud del objeto posUsuario
double Usuario::getLatitud(){
        return posUsuario->getLatitud();
}

// Obtiene longitud del objeto posUsuario
double Usuario::getLongitud(){
        return posUsuario->getLongitud();
}

// Retorna por referencia la posición del usuario en Json
bool Usuario::getPosUsuarioJson(std::string* posJ){
    posUsuario->getPosicionUsuarioJson(posJ);
    return true;
}
std::string Usuario::getTokenUsuario(){
    return token;
}

void Usuario::setTokenusuario(std::string* tok){
    token = *tok;
}

Usuario::Usuario(int* idUsuarioCons,std::string* nicknameCons,std::string* tok,
      int* lvlUsuario, int* vida, int*vidaMax,double* lon, double* lati){
        token= *tok;
        idUsuario = *idUsuarioCons; 
        nickName = *nicknameCons; 
        nivelUsuario = *lvlUsuario; 
        vidaUsuario = *vida; 
        vidaMaxUsuario = *vidaMax; 
        posUsuario = new PosicionUsuario(lon,lati,idUsuarioCons);
        
} 

Usuario::Usuario(std::string* rpl)
{
    Json::Reader readerJson; // Conversor de string Json a Objeto Json
    Json::Value usuario; // Objeto contenedor del documento Json
    std::string posJson; 
    // Se realiza la conversión del archivo Json a Objeto 
    if(!readerJson.parse(*rpl,usuario)) // Se verifica que se realice correctamente la conversion
    {
        std::cout  << "Error en la conversión de documento Json a Objeto Json\n"
       << readerJson.getFormattedErrorMessages();
    }

    // Se obtiene el valor de cada campo de acuerdo a la clave, en caso de no encontrarse retorna "Not found"
    idUsuario = std::stoi(usuario.get("idUsuario", "Not Found" ).asString()); 
    nickName = usuario.get("nickName", "Not Found" ).asString(); 
    nivelUsuario = std::stoi(usuario.get("nivelUsuario", "Not Found" ).asString()); 
    vidaUsuario = std::stoi(usuario.get("vidaUsuario", "Not Found" ).asString()); 
    poderAtaque = std::stoi(usuario.get("poderAtaque", "Not Found" ).asString()); 
    vidaMaxUsuario = std::stoi(usuario.get("vidaMaxUsuario", "Not Found" ).asString()); 
    posJson = usuario.get("posUsuario", "Not Found" ).asString(); 
    posUsuario = new PosicionUsuario(&posJson);
    token = usuario.get("token", "null" ).asString();
}

// realiza la conversión del Usuario a objeto Json
bool Usuario::usuarioToJson(std::string* usuarioJson){
    Json::Value root;  // Objeto Json 
    Json::FastWriter writer; // Conversor de objeto Json a formato string 
    std::string posJson;

    // En el objeto json se crean campos "clave":"valor"
    root["idUsuario"] = idUsuario; 
    root["nickName"] = nickName;
    root["nivelUsuario"] = nivelUsuario;
    root["vidaUsuario"] = vidaUsuario;
    root["vidaMaxUsuario"] = vidaMaxUsuario;
    root["poderAtaque"] = poderAtaque;
    posUsuario->getPosicionUsuarioJson(&posJson);
    root["posUsuario"] = posJson;
    root["token"] = token;

    // Se convierte el Objeto Json a formato String
    *usuarioJson = writer.write(root);

    return true;
}



