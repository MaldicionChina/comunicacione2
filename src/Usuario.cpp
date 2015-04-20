#include "Usuario.hpp"

  
int Usuario::getIdUsuario(){
        return idUsuario;
    }

std::string Usuario::getNickName(){
        return nickName;
}

double Usuario::getLatitud(){
        return posUsuario->getLatitud();
}

double Usuario::getLongitud(){
        return posUsuario->getLongitud();
}

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


Usuario::Usuario(int* idUsuarioCons,std::string* nicknameCons,
      int* lvlUsuario, int* vida, int*vidaMax,double* lon, double* lati){
        
        idUsuario = *idUsuarioCons; 
        nickName = *nicknameCons; 
        nivelUsuario = *lvlUsuario; 
        vidaUsuario = *vida; 
        vidaMaxUsuario = *vidaMax; 
        // longitud = *lon; 
        // latitud = *lati; 
        posUsuario = new PosicionUsuario(lon,lati,idUsuarioCons);
        
    } // Constructor

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

    idUsuario = std::stoi(usuario.get("idUsuario", "Not Found" ).asString()); 
    nickName = usuario.get("nickName", "Not Found" ).asString(); 
    nivelUsuario = std::stoi(usuario.get("nivelUsuario", "Not Found" ).asString()); 
    vidaUsuario = std::stoi(usuario.get("vidaUsuario", "Not Found" ).asString()); 
    poderAtaque = std::stoi(usuario.get("poderAtaque", "Not Found" ).asString()); 
    vidaMaxUsuario = std::stoi(usuario.get("vidaMaxUsuario", "Not Found" ).asString()); 
    // longitud = usuario.get("idUsuario", "Not Found" ).asString(); 
    // latitud = usuario.get("idUsuario", "Not Found" ).asString(); 
    posJson = usuario.get("posUsuario", "Not Found" ).asString(); 
    posUsuario = new PosicionUsuario(&posJson);
    token = usuario.get("token", "null" ).asString();
} // constructor


// realiza la conversión del Usuario a objeto Json
bool Usuario::usuarioToJson(std::string* usuarioJson){
    Json::Value root;  // Objeto Json 
    Json::FastWriter writer; // Conversor de objeto Json a formato string 
    std::string posJson;

    // root["idObjecto"] = nombreClase;
    root["idUsuario"] = idUsuario;
    root["nickName"] = nickName;
    root["nivelUsuario"] = nivelUsuario;
    root["vidaUsuario"] = vidaUsuario;
    root["vidaMaxUsuario"] = vidaMaxUsuario;
    root["poderAtaque"] = poderAtaque;
    // root["longitud"] = longitud;
    // root["latitud"] = latitud;
    posUsuario->getPosicionUsuarioJson(&posJson);
    root["posUsuario"] = posJson;
    root["token"] = token;

    *usuarioJson = writer.write(root);

    return true;
}



