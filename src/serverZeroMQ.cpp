 
#include <zmq.hpp>
#include <string>
#include <iostream>
#include <json/json.h>
#include <sstream>
#include "Usuario.hpp"
#include <pthread.h>
#include <unistd.h>
#include <cassert>
#include <Recursos.hpp>

// 3 6.2652965,-75.5714428
// 1 6.2706908,-75.5699971
// 2 6.2695098,-75.5666914
// 4 6.2648545,-75.5676569,21

struct recurso_t
{
    Recursos* manejador_juego;
    zmq::context_t* contex;
}recursos_juego;

// Permite la ejecución de hilos
void *worker_routine (void *arg)
{

    std::string replyServer ="Ok";
    Json::Value mensajeCliente;
    Json::Reader readerJson; // Para relizar conversiones de string a objeto Json
    std::string tipoObjeto; // Almacena el tipo de obejto
    std::string data; // 

    struct recurso_t* contenedor_recursos = (struct recurso_t*) arg;

    zmq::context_t *context = contenedor_recursos->contex;

    zmq::socket_t socket (*context, ZMQ_REP);
    socket.connect ("inproc://workers");

    while (true) {
        // Variable para almacenar el mensaje entrante
        zmq::message_t request;
        //  Espera por algún mensaje de los usuarios
        socket.recv (&request);
        // std::cout << "Received request: [" << (char*) request.data() << "]" << std::endl;

        // Conversión de message_t a string
        std::string preJson = std::string(static_cast<char*>(request.data()), request.size()); 
//     // std::cout << rpl  << std::endl;

        // Se verifica que se realice correctamente la conversion
        if(!readerJson.parse(preJson,mensajeCliente)) 
        {
            std::cout  << "Error en la conversión de documento Json a Objeto Json\n"
                 << readerJson.getFormattedErrorMessages();
        }

        // idObjeto contiene la indentificación de qué objeto debemos tratar
        tipoObjeto = mensajeCliente.get("idObjeto", "Not Found" ).asString(); // se obtiene el valor en la clave 'idObjeto'
        data = mensajeCliente.get("data", "Not Found" ).asString(); // se obtiene el valor en la clave 'data'
        if( tipoObjeto == "usuario"){
             Usuario* user = new Usuario(&data); //Se crear el conjeto a partir del Json en formato String
             std::cout << "Usuario  "<< user->getNickName() << " conectado desde" << std::endl 
                       << "Latitud: "<< user->getLatitud() << " Longitud: "<< user->getLongitud()<< std::endl;
        }else if (tipoObjeto == "ataque"){

        }else if (tipoObjeto == "posUsuario"){

        }else if (tipoObjeto == "login"){

        }else{
               std::cout << "Json sin identificacion de Objeto "<< std::endl;
        }
//     //  Do some 'work'
//     //        sleep(1);

        //Conversión de string a stringstream para enviarlo por al red
        std::stringstream lineStream(replyServer);

//     // Conversión de stringstreamer a zmq::message_t
        zmq::message_t reply ((void*)lineStream.str().c_str(), lineStream.str().size()+1, NULL);
        socket.send (reply);
    }
    return (NULL);
}


int main (int argc, char *argv[]) {

  //Prepare our context and socket
  zmq::context_t context (1);
  // zmq::socket_t socket (context, ZMQ_REP);
  // socket.bind ("tcp://*:5555");  

  int totalUsuarios = 5;

  zmq::socket_t clients (context, ZMQ_ROUTER);
  clients.bind ("tcp://*:5555");
  zmq::socket_t workers (context, ZMQ_DEALER);
  workers.bind ("inproc://workers");

  recursos_juego.manejador_juego = new Recursos(5);
  recursos_juego.contex = &context;

  for (int thread_nbr = 0; thread_nbr != 5; thread_nbr++) {
      pthread_t worker;
      pthread_create (&worker, NULL, worker_routine, (void *) &recursos_juego);
  }
  
  zmq::proxy (clients, workers, NULL);
  return 0;

  // int count = 0;
  // std::cout << "Listen in port 5555" << std::endl;
  
  // while (true) {
  //     zmq::message_t request;
  //     //  Espera por algún mensaje de los usuarios
  //     socket.recv (&request);
  //     // Conversión de message_t a string
	 //    std::string rpl = std::string(static_cast<char*>(request.data()), request.size()); 
  //     // std::cout << rpl  << std::endl;

  //     if(!readerJson.parse(rpl,mensajeCliente)) // Se verifica que se realice correctamente la conversion
  //     {
  //         std::cout  << "Error en la conversión de documento Json a Objeto Json\n"
  //              << readerJson.getFormattedErrorMessages();
  //     }

  //     // idObjeto contiene la indentificación de qué objeto debemos tratar
  //     tipoObjeto = mensajeCliente.get("idObjeto", "Not Found" ).asString(); // se obtiene el valor en la clave 'idObjeto'
  //     data = mensajeCliente.get("data", "Not Found" ).asString(); // se obtiene el valor en la clave 'data'
  //     if( tipoObjeto == "usuario"){
  //       Usuario user(&data); //Se crear el conjeto a partir del Json en formato String
  //       std::cout << "Usuario  "<< user.getNickName() << " conectado desde" << std::endl 
  //                 << "Latitud: "<< user.getLatitud() << " Longitud: "<< user.getLongitud()<< std::endl;
  //     }else if (tipoObjeto == "ataque"){

  //     }else if (tipoObjeto == "posUsuario"){

  //     }else if (tipoObjeto == "login"){

  //     }else{
  //       std::cout << "Json sin identificacion de Objeto "<< std::endl;
  //     }
  //     //  Do some 'work'
  //     //        sleep(1);

  //     //Responde al mensaje de los usuarios
  //     std::stringstream lineStream(replyServer);

  //     // Conversión de stringstreamer a zmq::message_t
  //     zmq::message_t reply ((void*)lineStream.str().c_str(), lineStream.str().size()+1, NULL);
  //     socket.send (reply);
  //     count = count + 1;
  //   }
  //   return 0;
}
