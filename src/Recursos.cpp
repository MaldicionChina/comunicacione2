#include "Recursos.hpp"

Recursos::Recursos(int totalUsuarios){
	maximoConectados = totalUsuarios; 
}

bool Recursos::conectar(Usuario* user){

	if(maximoConectados > totalConectados){
		usuarios.push_back(user);
		totalConectados = totalConectados + 1;
		return true;
	}
	return false;
}

bool Recursos::atacarUsuario(int idAtacante, int idAtacado){

}

int Recursos::getUsuariosConectadosJson(std::string* conectadosJson){

	std::string posJson;
	Json::Value conectados;  // Objeto Json 
	Json::FastWriter writer; // Conversor de objeto Json a formato string 

	if(totalConectados>0){
    // root["idObjecto"] = nombreClase;

		for(int j = 0; j < usuarios.size(); j++){
			    usuarios.at(j)->getPosUsuarioJson(&posJson);
			    conectados[j] = posJson;
			}
			*conectadosJson = writer.write(conectados);
			// std::cout << "Posiciones "<< std::endl << writer.write(conectados) << std::endl;
		}
	return totalConectados;
}


bool Recursos::getUsuarioById(int idUser, Usuario* user){

	// std::cout << "Tamaño usuarios "<< usuarios.size() << std::endl;
	// std::cout << "algo... "<<usuarios.at(idUser)->getIdUsuario() << std::endl;
	std::string usuarioJson; 
	
	for(int i = 0; i < usuarios.size(); i++){
		if(usuarios.at(i)->getIdUsuario()==idUser){
			// usuarios.at(i)->getNickName();
			usuarios.at(i)->usuarioToJson(&usuarioJson);
			std::cout << "Id...."<< usuarioJson << std::endl;
			// Usuario* salida = new Usuario(&);
			return true;
		}
	}
	return false;
}

bool Recursos::desconectar(int idUsuario){
	
	for(unsigned i = 0; i <= usuarios.size(); i++){
		if(usuarios.at(i)->getIdUsuario()== idUsuario){
			usuarios.erase(usuarios.begin()+i); // Borra el usuario de la lista
			totalConectados = totalConectados - 1;
			return true;
		}
	}	
	return false; // el usuario no existe
}

bool Recursos::actualizarPosicionUsuario(PosicionUsuario* posUser){
	return false;
}

int Recursos::getTotalConectados(){
	return totalConectados;
}
