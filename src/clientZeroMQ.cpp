//
//  Hello World client in C++
//  Connects REQ socket to tcp://localhost:5555
//  Sends "Hello" to server, expects "World" back
//
#include <zmq.hpp>
#include <string>
#include <iostream>
#include "Usuario.hpp"
#include <json/json.h>

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

    std::cout << "ID jugador: "<< jugaa->getIdUsuario() << std::endl;

    Json::Value root; 
 
    
   	// Prepare our context and socket
   // 	zmq::context_t context (1);
   // 	zmq::socket_t socket (context, ZMQ_REQ);

   // 	std::cout << "Connecting to hello world server…" << std::endl;
   // 	socket.connect ("tcp://localhost:5555");

   // //  Do 10 requests, waiting each time for a response
   // 	for (int request_nbr = 0; request_nbr != 10; request_nbr++) {
   //     zmq::message_t request (6);
   //     memcpy ((void *) request.data (), "Hello", 5);
   //     std::cout << "Sending Hello " << request_nbr << "…" << std::endl;
   //     socket.send (request);

   //     //  Get the reply.
   //     zmq::message_t reply;
   //     socket.recv (&reply);
   //     std::cout << "Received World " << request_nbr << std::endl;
   // 	}
   
    delete jugaa;
    return 0;
}