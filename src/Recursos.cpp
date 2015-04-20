#include "Recursos.hpp"

Recursos::Recursos(int totalUsuarios){
	maximoConectados = totalUsuarios; 
}

bool Recursos::conectar(Usuario* user){

	if(maximoConectados < totalConectados){
		totalConectados = totalConectados+1;

	}
}

bool Recursos::actualizarPosicionUsuario(PosicionUsuario* posUser){
	return false;
}