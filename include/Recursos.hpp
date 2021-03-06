#ifndef RECURSOS_HPP
#define	RECURSOS_HPP

#include <iostream>
#include <list>
#include <Usuario.hpp>
#include <vector>
#include "PosicionUsuario.hpp"
#include <time.h> 
#include "Ataque.hpp"

#define LADITOS_SIN_RESPUESTA  3       // total de latidos antes de la desconexión del usuario
#define INTERVALO_ENTRE_LATIDOS  1000  //  msecs
#define PODER_ATAQUE 2

struct latido {
	int idUsuario; // Identificación del usuario
	time_t latido; // contro de latido
	int latidosPerdidos; // total latidos perdidos
};

class Recursos{
public:
	// Constructor que recibe el número máximo de usuario conectados
	Recursos(int totalUsuarios);
	// Metodo para conectar los usuarios al servidor, se debe haber relizado login antes de este metodo
	bool conectar(Usuario* user);

	bool desconectar(int idUsuario);

	// El usuario enviá su posición cada x seg, se hará control de hearbet con está función
	bool actualizarPosicionUsuario(PosicionUsuario* posUser);

	int getTotalConectados();

	bool atacarUsuario(Ataque* atac);

	// Aún sin implementar totalmente
	std::string getUsuarioByIdJson(int idUser);

	// Se obtiene la posicion y el identificador del usuario en un documento json
	// Retorna el total de usuarios conectados
	int getUsuariosConectadosJson(std::string* conectadosJson,int idUsuarioEnviar);


private:
	// conexiones vigentes
	int totalConectados = 0;
	// Maximas conexciones permitidas
	int maximoConectados;
	// Lista de Usuarios Conectados
	std::vector<Usuario*> usuarios;
	std::vector<latido> latidos;

	double segundosLatido = INTERVALO_ENTRE_LATIDOS;
	int totalLatidosSinRepuesta = INTERVALO_ENTRE_LATIDOS;
};
#endif	/* RECURSOS_HPP */