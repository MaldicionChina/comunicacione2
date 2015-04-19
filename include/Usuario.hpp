
#ifndef Usuario_HPP
#define	Usuario_HPP

#include <iostream>
#include <json/json.h>
#include "PosicionUsuario.hpp"

class Usuario{
private:
    int idUsuario; // ID único que identifica inequivocamente al Usuario en todo el juego
    std::string nickname; // Nombre en el juego para el Usuario
    int nivelUsuario; // Nivel en el juego del Usuario
    int vidaUsuario; // Vida actual de usuario 
    int vidaMaxUsuario; // Vida total que puede tener el usuario; varia de acuerdo al nivel
    int posX; // Indice X para la posición en la cuadricula
    int posY; // Indice Y para lara posición en la cuadricula
    double longitud; // Dato correspondiente e la longitud de la pocisión del usuario
    double latitud; // Dato correspondiente e la latitud de la pocisión del usuario
    
    const std::string nombreClase = "Usuario";
    
public:
    Usuario(int* idUsuarioCons,std::string* nicknameCons,
      int* lvlUsuario, int* vida, int*vidaMax,double* lon, double* lati); // Constructor  

    // Usuario(int* idUsuarioCons,std::string* nicknameCons,
    //   int* lvlUsuario, int* vida, int*vidaMax,PosicionUsuario* posuser);  // COnstructor que recibe objeto PosicionUsuario
    
    int getIdUsuario(); // Obtener el id del Usuario

    bool usuarioToJson(std::string* usuarioJson);
    PosicionUsuario* posUsuario; 
    // Atributo publico ya que le objeto Posicion Usuario tiene el objeto 
    // PosicionUsario tiene el meteodo para convertir a Json
    

    /*Convierte el idUsuario, longitud y latitud a Json
    Devuelve por el parametro el archivo Json
    retorna bool para verificar que se realizó la conversión sin promeblas
    Retorna el id, latitud y longitud
    */
    bool getPosUsuarioJson(std::string* posJson);
};


#endif	/* Usuario_HPP */

