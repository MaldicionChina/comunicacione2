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

bool Recursos::atacarUsuario(Ataque* atac){

	for(int i = 0; i < usuarios.size(); i++){
		if(usuarios.at(i)->getIdUsuario()==atac->getIdAtacado()){
			usuarios.at(i)->perderVida(PODER_ATAQUE);
			return true;
		}
	}
}

// Retorna la posición en documento Json de todos los usuario conectados
int Recursos::getUsuariosConectadosJson(std::string* conectadosJson, int idUsuarioEnviar){

	std::string posJson;
	Json::Value conectados;  // Objeto Json 
	Json::FastWriter writer; // Conversor de objeto Json a formato string 

	if(totalConectados>0){

		for(int j = 0; j < usuarios.size(); j++){
				if(idUsuarioEnviar!=usuarios.at(j)->getIdUsuario()){
			    	usuarios.at(j)->getPosUsuarioJson(&posJson);
			    	conectados["posUsuarios"] = posJson;
			    }
			}
			*conectadosJson = writer.write(conectados);
		}
	return totalConectados;
}

// PELIGRO: Revisar Utilidad de este metodo
std::string Recursos::getUsuarioByIdJson(int idUser){

	std::string usuarioJson; 
	// Se realiza la busqueda del usuario en la lista de usuario conectados
	for(int i = 0; i < usuarios.size(); i++){
		if(usuarios.at(i)->getIdUsuario()==idUser){
			usuarios.at(i)->usuarioToJson(&usuarioJson);
			return usuarioJson;
		}
	}
	return "null";
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

	int idUsuarioActualizar = posUser->getIdUsuario();

	// Se realiza la busqueda del usuario en la lista de usuario conectados
	for(int j = 0; j < usuarios.size(); j++){
		if(idUsuarioActualizar==usuarios.at(j)->getIdUsuario()){
			usuarios.at(j)->actualizarPos(posUser);
			return true;
		}
	}
	return false; // Usuario no concetado
}
	


int Recursos::getTotalConectados(){
	return totalConectados;
}
