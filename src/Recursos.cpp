#include "Recursos.hpp"

Recursos::Recursos(int totalUsuarios){
	maximoConectados = totalUsuarios; 
}

bool Recursos::conectar(Usuario* user){

	if(maximoConectados < totalConectados){
		usuarios.push_back(user);
		totalConectados = totalConectados + 1;
	}
}

bool Recursos::desconectar(int idUsuario){
	
	for(int i = 1; i <= totalConectados; i++){
		if(usuarios[i]->getIdUsuario()== idUsuario){
			usuarios.erase(usuarios.begin()+i); // Borra el usuario de la lista
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
