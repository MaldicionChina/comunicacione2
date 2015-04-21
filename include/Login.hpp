#include <iostream>
#include <Usuario.hpp> 
#include <curl/curl.h>
class Login {
    private:
    int atacado;//id del atacado
    int atacante;//id del atacante
    
    public:

   Login(std::string nickName, std::string password);//Constructor de la clase
   Usuario Autentificar();//metodo que autentifica un Usuario en caso de de hacer el login retorna usuario, si no retorna null 
   void CerrarSesion(int idUsuario);//metodo para destruir la sesion del usuario
};
#endif
