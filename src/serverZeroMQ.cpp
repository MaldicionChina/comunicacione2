 
// autor: Alexis Rodríguez Gutiérrez 
// Prueba Listen Server con C++ y ZeroMQ

#include <zmq.hpp>
#include <string>
#include <iostream>
#include <json/json.h>
#include <sstream>
#ifndef _WIN32
  #include <unistd.h>
#else
  #include <windows.h>
  #define sleep(n)    Sleep(n)
#endif

// 3 6.2652965,-75.5714428
// 1 6.2706908,-75.5699971
// 2 6.2695098,-75.5666914
// 4 6.2648545,-75.5676569,21


int main (int argc, char *argv[]) {

  std::string replyServer ="Ok";
  Json::Value mensajeCliente;


  
  //Prepare our context and socket
  zmq::context_t context (1);
  zmq::socket_t socket (context, ZMQ_REP);
  socket.bind ("tcp://*:5555");
  
  int count = 0;
  std::cout << "Listen in port 5555" << std::endl;
  
  while (true) {
      zmq::message_t request;

      //  Espera por algún mensaje de los usuarios
      socket.recv (&request);
	    std::string rpl = std::string(static_cast<char*>(request.data()), request.size()); // COnversión de message_t a string
      std::cout << rpl  << std::endl;


      Json::Reader readerJson;
      // Se realiza la conversión del archivo Json a Objeto 
      if(readerJson.parse(rpl,mensajeCliente)) // Se verifica que se realice correctamente la conversion
      {
          std::cout  << "Error en la conversión de documento Json a Objeto Json\n"
               << readerJson.getFormattedErrorMessages();
      }
      
      std::cout << "El objeto es de tipo: "<< mensajeCliente.get("IdObjecto", "Not Found" ).asString() << std::endl;

      //  Do some 'work'
      //        sleep(1);

      //Responde al mensaje de los usuarios
      std::stringstream lineStream(replyServer);

      zmq::message_t reply ((void*)lineStream.str().c_str(), lineStream.str().size()+1, NULL);
      // memcpy ((void *) reply.data (), "0", 1);
	
      socket.send (reply);
      count = count + 1;
    }
    return 0;
}
