//
//  Hello World client in C++
//  Connects REQ socket to tcp://localhost:5555
//  Sends "Hello" to server, expects "World" back
//
#include <zmq.hpp>
#include <string>
#include <iostream>
#include "Usuario.hpp"
#include "PosicionUsuario.hpp"
#include <json/json.h>
#include <sstream>  

int main (int argc, char *argv[])
{


  std::string json_output; // Varaible para almacenar el string json resultante
  zmq::message_t reply;    //Variable para almacenar la respuesta del servidor

	std::string nombreJugador = "Hola";
	int idJugador = 5; 
	int nivelJudador = 3; 
	int vidaJudador = 100; 
	int vidaMaxUsuario = 100; 
	double longitud = 6.244747; 
	double latitud = -75.574828; 
  Usuario* jugaa = new Usuario(&idJugador,&nombreJugador,&nivelJudador,&vidaJudador
    	,&vidaMaxUsuario,&longitud,&latitud);

  std::cout << "ID jugador: "<< jugaa->getIdUsuario() << std::endl;

  jugaa->usuarioToJson(&json_output); // Se obtiene el string json del usuario
  // jugaa->posUsuario->getPosicionUsuarioJson(&json_output);
  std::stringstream lineStream(json_output); // Conversión de string a stringstreamer para enviarlo por la red

  std::cout << "Json Posicion Usuario"<< json_output << std::endl;

  // Se prepara el contexto y el socket para iniciar la comunicación con el servidor
  zmq::context_t context (1);
  zmq::socket_t socket (context, ZMQ_REQ); // socket de tipo REQUEST

  std::cout << "Connecting to hello world server…" << std::endl;
  socket.connect ("tcp://localhost:5555"); // el socket se connecta

  // Se hace la conversión de stringstreamer a message_t(formato que acepta zmq) para enviarlo por red
  zmq::message_t request((void*)lineStream.str().c_str(), lineStream.str().size()+1, NULL);

  std::cout << "Sending Hello " << (const char*)request.data()<< "…" << std::endl;
  // Se envia el mensaje
  socket.send (request);

  // Se recibe el mensaje del servidor
  socket.recv (&reply);
  std::string rpl = std::string(static_cast<char*>(reply.data()), reply.size()); // COnversión de message_t a string
  std::cout << rpl.data() << std::endl;

  // zmq_close(socket);
  // zmq_ctx_destroy(context);

  delete jugaa;
  return 0;
}