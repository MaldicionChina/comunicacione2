#ifndef LOGIN_HPP
#define	LOGIN_HPP

#include <iostream>
#include <Usuario.hpp> 
#include <curl/curl.h>

class Login {
    private:
    std::string correo;//id del atacado
    std::string contrasena;//id del atacante

    public:
   	Login(std::string* jsonLogin);//Constructor de la clase
   	Login(std::string cor,std::string contra);
   	Usuario Autentificar();//metodo que autentifica un Usuario en caso de de hacer el login retorna usuario, si no retorna null 
   	std::string getCorreo();
   	std::string getContrasena();
   	void CerrarSesion(int idUsuario);//metodo para destruir la sesion del usuario
   	std::string getLoginJson();
};
#endif
