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
Usuario::Usuario(int* idUsuarioCons,std::string* nicknameCons,
      int* lvlUsuario, int* vida, int*vidaMax,double* lon, double* lati){
        
        idUsuario = *idUsuarioCons; 
        nickName = *nicknameCons; 
        nivelUsuario = *lvlUsuario; 
        vidaUsuario = *vida; 
        vidaMaxUsuario = *vidaMax; 
        estadoUsuario = "vivo";
        posUsuario = new PosicionUsuario(lon,lati,idUsuarioCons);
        
} 

bool Usuario::perderVida(int restar){

    if(estadoUsuario=="vivo")
    {
        if(vidaUsuario > restar)
        {
            vidaUsuario = vidaUsuario - restar;
            return true;
        }else{
            vidaUsuario = 0;
            estadoUsuario = "muerto";
            return false;
        }
    }
}

Usuario::Usuario(std::string* rpl)
{
    Json::Reader readerJson; // Conversor de string Json a Objeto Json
    Json::Value usuario; // Objeto contenedor del documento Json
    std::string posJson; 
    // Se realiza la conversión del archivo Json a Objeto 
    // std::cout << "rpl..." << *rpl << std::endl;
    if(!readerJson.parse(*rpl,usuario)) // Se verifica que se realice correctamente la conversion
    {
        std::cout  << "Error en la conversión de documento Json a Objeto Json\n"
       << readerJson.getFormattedErrorMessages();
    }

    // Se obtiene el valor de cada campo de acuerdo a la clave, en caso de no encontrarse retorna "Not found"
    idUsuario = std::stoi(usuario.get("idUsuario", "\"1\"" ).asString()); 
    nickName = usuario.get("nickName", "not" ).asString(); 
    nivelUsuario = std::stoi(usuario.get("nivelUsuario", "\"1\"" ).asString()); 
    vidaUsuario = std::stoi(usuario.get("vidaUsuario", "\"1\"" ).asString()); 
    token = usuario.get("token", "null" ).asString();
    posJson = usuario.get("posUsuario", "null" ).asString(); 
    if(posJson != "null")
    {
        posUsuario = new PosicionUsuario(&posJson);
    }else{
        double latitud = 6.2652965;
        double longitud = -75.5714428;
        posUsuario = new PosicionUsuario(&latitud,&longitud,&idUsuario);
        poderAtaque = 3; 
        vidaMaxUsuario = 100; 
        estadoUsuario = "vivo";
    }
}

// realiza la conversión del Usuario a objeto Json, retorna el Json por refenencia
bool Usuario::usuarioToJson(std::string* usuarioJson){
    Json::Value root;  // Objeto Json 
    Json::FastWriter writer; // Conversor de objeto Json a formato string 
    std::string posJson;

    // En el objeto json se crean campos "clave":"valor"
    root["idUsuario"] = idUsuario; 
    root["nickName"] = nickName;
    root["nivelUsuario"] = nivelUsuario;
    root["estadoUsuario"] = estadoUsuario;
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



