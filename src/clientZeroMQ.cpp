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

int main ()
{
	std::string nombreJugador = "Hola";
	int idJugador = 5; 
	int nivelJudador = 3; 
	int vidaJudador = 100; 
	int vidaMaxUsuario = 100; 
	double longitud = 3.4; 
	double latitud = 4.5; 
  Usuario* jugaa = new Usuario(&idJugador,&nombreJugador,&nivelJudador,&vidaJudador
    	,&vidaMaxUsuario,&longitud,&latitud);

  size_t tamanoMensajeJson = 0;

  std::cout << "ID jugador: "<< jugaa->getIdUsuario() << std::endl;

  // Prueba Json
  // Json::Value root;   // starts as "null"; will contain the root value after parsing
  // Json::FastWriter writer;

  // root["IdObjecto"] = 1;

  std::string json_output;
  jugaa->posUsuario->getPosicionUsuarioJson(&json_output);

  std::stringstream lineStream(json_output);
  std::cout << "Json Pos "<< json_output << std::endl;
  // Prepare our context and socket
  zmq::context_t context (1);
  zmq::socket_t socket (context, ZMQ_REQ);

  std::cout << "Connecting to hello world server…" << std::endl;
  socket.connect ("tcp://localhost:5555");
  // tamanoMensajeJson = json_output.length();
  // zmq::message_t request (tamanoMensajeJson);
  // memcpy ((void *) request.data (), json_output, tamanoMensajeJson);
  zmq::message_t request((void*)lineStream.str().c_str(), lineStream.str().size()+1, NULL);
  std::cout << "Sending Hello " << (const char*)request.data()<< "…" << std::endl;
  socket.send (request);

   //     //  Get the reply.
  zmq::message_t reply;
  socket.recv (&reply);
  std::cout << "Received World " << std::endl;
  // 	}
  // zmq_close(socket);
  // zmq_term(context);

  zmq_close(socket);
  zmq_ctx_destroy(context);

  delete jugaa;
  return 0;
}