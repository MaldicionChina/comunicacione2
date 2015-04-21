
#ifndef Usuario_HPP
#define	Usuario_HPP

#include <iostream>
#include <json/json.h>
#include "PosicionUsuario.hpp"
#include <time.h> 

class Usuario{
private:
    int idUsuario; // ID único que identifica inequivocamente al Usuario en todo el juego
    std::string nickName; // Nombre en el juego para el Usuario
    int nivelUsuario; // Nivel en el juego del Usuario
    int vidaUsuario; // Vida actual de usuario 
    int vidaMaxUsuario; // Vida total que puede tener el usuario; varia de acuerdo al nivel
    int posX; // Indice X para la posición en la cuadricula
    int posY; // Indice Y para lara posición en la cuadricula
    std::string estadoUsuario; // el usuario está Vivo o muerto ?
    PosicionUsuario* posUsuario; 
    std::string token = "null";
    int poderAtaque = 1;

public:
    Usuario(int* idUsuarioCons,std::string* nicknameCons,
      int* lvlUsuario, int* vida, int*vidaMax,double* lon, double* lati); // Constructor  

    Usuario(std::string*); // Constructor a partir de un documento Json en formato string
 
    int getIdUsuario(); // Obtener el id del Usuario
    std::string getNickName();
    double getLatitud();
    double getLongitud();

    bool usuarioToJson(std::string* usuarioJson);
    bool jsonToUsuario(std::string*);
    double getPosUsuario();
    void setTokenusuario(std::string* tok);
    std::string getTokenUsuario();
    bool actualizarPos(PosicionUsuario* posActualizar);
    bool perderVida(int restar);


   /*Convierte el idUsuario, longitud y latitud a Json devuelve por el parametro el archivo Json
    retorna bool para verificar que se realizó la conversión sin promeblas 
    Retorna el id, latitud y longitud en formato Json
    */
    bool getPosUsuarioJson(std::string* posJ);
};

#endif	/* Usuario_HPP */

