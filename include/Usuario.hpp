
#ifndef Usuario_HPP
#define	Usuario_HPP

#include <iostream>

class Usuario{
private:
    int idUsuario; // ID único que identifica inequivocamente al Usuario en todo el juego
    std::string nickname; // Nombre en el juego para el Usuario
    int nivelUsuario; // Nivel en el juego del Usuario
    int vidaUsuario; // Vida actual de usuario 
    int vidaMaxUsuario; // Vida total que puede tener el usuario; varia de acuerdo al nivel
    double longitud; // Dato correspondiente e la longitud de la pocisión del usuario
    double latitud; // Dato correspondiente e la latitud de la pocisión del usuario
    
public:
    Usuario(int* idUsuarioCons,std::string* nicknameCons,
      int* lvlUsuario, int* vida, int*vidaMax,double* lon, double* lati); // Constructor    
    
    int getIdUsuario(); // Obtener el id del Usuario
};


#endif	/* Usuario_HPP */

