#include "Usuario.hpp"

Usuario::Usuario(int* idUsuarioCons,std::string* nicknameCons,
      int* lvlUsuario, int* vida, int*vidaMax,double* lon, double* lati){
        
        idUsuario = *idUsuarioCons; 
        nickname = *nicknameCons; 
        nivelUsuario = *lvlUsuario; 
        vidaUsuario = *vida; 
        vidaMaxUsuario = *vidaMax; 
        longitud = *lon; 
        latitud = *lati; 
        posUsuario = new PosicionUsuario(lon,lati,idUsuarioCons);
        
    } // Constructor
    
int Usuario::getIdUsuario(){
        return idUsuario;
    }


// realiza la conversión del Usuario a objeto Json
bool Usuario::usuarioToJson(std::string* usuarioJson){
    Json::Value root;  
    Json::FastWriter writer;
    std::string posJson;
    root["idObjecto"] = nombreClase;
    root["idUsuario"] = idUsuario;
    root["nickName"] = nickname;
    root["nivelUsuario"] = nivelUsuario;
    root["vidaUsuario"] = vidaUsuario;
    root["vidaMaxUsuario"] = vidaMaxUsuario;
    root["longitud"] = longitud;
    root["latitud"] = latitud;
    posUsuario->getPosicionUsuarioJson(&posJson);
    root["posUsuario"] = posJson;

    *usuarioJson = writer.write(root);

    return true;
}

// bool Usuario::getPosUsuarioJson(std::string* posJson){

//     Json::Value root;   // starts as "null"; will contain the root value after parsing
//     Json::FastWriter writer;
//     root["IdObjecto"] = "posUsuario";
//     root["IdUsuario"] = idUsuario;
//     root["longitud"] = longitud;
//     root["latitud"] = latitud;

//     *posJson = writer.write(root);

//     return true;
// }