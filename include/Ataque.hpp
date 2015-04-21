#ifndef ATAQUE_HPP
#define	ATAQUE_HPP
#include "json/json.h"
#include <iostream>

class Ataque {
    private:
    int _atacado;//id del atacado
    int _atacante;//id del atacante
    
    public:
    // Creca el objeto con el usuario que ataca y con el usuario a quién va dirigido el ataque
    Ataque(int atacante, int atacado);//Constructor de la clase
      // Recibe por referencia el objeto Json con la información del ataque
    Ataque(std::string* ataque);

    // Retornar por referencia el objeto Ataque en Json formato string
    bool ataqueToJson(std::string* ataque);

    int getIdAtacante();
    int getIdAtacado();
  
    // bool jsonToAtaque(std::string* ataque);
};
#endif
