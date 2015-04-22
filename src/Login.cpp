#include "Login.hpp"

Login::Login(std::string cor,std::string contra){
	correo = cor;
	contrasena = contra;
}

Login::Login(std::string* jsonLogin){
	Json::Reader readerJson;
	Json::Value login;

    if(!readerJson.parse(*jsonLogin,login)) // Se verifica que se realice correctamente la conversion
    {
        std::cout  << "Error en la conversión de documento Json a Objeto Json\n" 
        << readerJson.getFormattedErrorMessages();

    }else{

	correo = login.get("correo", "Not Found" ).asString(); //id del atacado
    contrasena = login.get("contrasena", "Not Found" ).asString(); ;//id del atacante
	}
}

std::string Login::confirmarConexion(std::string* jsonLogin){
	Json::Reader readerJson;
	Json::Value logi;
	Json::Value datos;
	std::string error;
	std::string dataUsuario;
	Json::FastWriter writer; 

	if(!readerJson.parse(*jsonLogin,logi)) // Se verifica que se realice correctamente la conversion
    {
        std::cout  << "Error en la conversión de documento Json a Objeto Json\n" 
        << readerJson.getFormattedErrorMessages();

    }else{
    	error = logi.get("error", "Not_Found" ).asString();
    	if(error == "Not_Found")
    	{
    		datos = logi.get("response", "Not Found"); 
    		dataUsuario = writer.write(datos);
    		return dataUsuario;
    		
     	}
   	}
   	return "NULL";

}

std::string Login::getLoginJson(){
	Json::Value login; // Objeto que almacena la estructura Json
    Json::FastWriter writer; //Conversor de Objeto Json a String Json

    // En el objeto json se crean campos "clave":"valor"
    login["correo"] = correo;
    login["contrasena"] = contrasena;
    // Se convierte el Objeto Json a formato String
    return writer.write(login);
}

std::string Login::getCorreo(){
	return correo;
}

std::string Login::getContrasena(){
	return contrasena;
}