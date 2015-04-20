#include <zmq.hpp>
#include <string>
#include <iostream>
#include "Usuario.hpp"
#include "PosicionUsuario.hpp"
#include <json/json.h>
#include <sstream>  

std::string enviarObjetoServer(zmq::socket_t* soc, std::string tipoObjeto, std::string* jsonObjetcString, zmq::message_t* reply){
  Json::Value enviar;
  Json::FastWriter writer;
  std::string mensaje;

  enviar["idObjeto"] = tipoObjeto;
  enviar["data"] = *jsonObjetcString;

  std::stringstream lineStream(writer.write(enviar));
  zmq::message_t request((void*)lineStream.str().c_str(), lineStream.str().size()+1, NULL);
  soc->send (request);

  // Do some work

  soc->recv (reply);
  std::string rpl = std::string(static_cast<char*>(reply->data()), reply->size()); // COnversión de message_t a string
  std::cout << rpl << "tamaño: " << reply->size() << std::endl;
  return rpl;
}

int main (int argc, char *argv[])
{

  std::string nombreCLiente;
  std::string json_output; // Varaible para almacenar el string json resultante
  zmq::message_t reply;    //Variable para almacenar la respuesta del servidor

  std::cout << "Bienvenido al Juego" << std::endl;

  if(argc != 3)
  {
      std::cout << argv[0] << " Id NombreJugador" << std::endl;
      return -1;
  }

	std::string nombreJugador = argv[2];
	int idJugador = std::stoi(argv[1]); 
	int nivelJudador = 3; 
	int vidaJudador = 100; 
	int vidaMaxUsuario = 100; 
	double longitud = 6.244747; 
	double latitud = -75.574828; 
  Usuario* jugaa = new Usuario(&idJugador,&nombreJugador,&nivelJudador,&vidaJudador
    	,&vidaMaxUsuario,&longitud,&latitud);

   // Se prepara el contexto y el socket para iniciar la comunicación con el servidor
  zmq::context_t context (1);
  zmq::socket_t socket (context, ZMQ_REQ); // socket de tipo REQUEST
  std::cout << "Connecting to hello world server…" << std::endl;
  socket.connect ("tcp://localhost:5555"); // el socket se connecta

  std::cout << "ID jugador: "<< jugaa->getIdUsuario() << std::endl;
  jugaa->usuarioToJson(&json_output); // Se obtiene el string json del usuario
  enviarObjetoServer(&socket,"usuario",&json_output,&reply);
  // // jugaa->posUsuario->getPosicionUsuarioJson(&json_output);
  // std::stringstream lineStream(json_output); // Conversión de string a stringstreamer para enviarlo por la red

  // // Se hace la conversión de stringstreamer a message_t(formato que acepta zmq) para enviarlo por red
  // zmq::message_t request((void*)lineStream.str().c_str(), lineStream.str().size()+1, NULL);

  // // std::cout << "Sending Hello " << (const char*)request.data()<< "…" << std::endl;
  // // Se envia el mensaje
  // socket.send (request);

  // // Se recibe el mensaje del servidor
  // socket.recv (&reply);
  // std::string rpl = std::string(static_cast<char*>(reply.data()), reply.size()); // COnversión de message_t a string
  // std::cout << rpl.data() << std::endl;

  // // zmq_close(socket);
  // // zmq_ctx_destroy(context);

  delete jugaa;
  return 0;
}