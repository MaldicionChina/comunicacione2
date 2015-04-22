 
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
#include <time.h> 
#include "Ataque.hpp"
#include "Login.hpp"

#include <curl/curl.h>
// 3 6.2652965,-75.5714428
// 1 6.2706908,-75.5699971
// 2 6.2695098,-75.5666914
// 4 6.2648545,-75.5676569,21

struct recurso_t
{
    Recursos* manejador_juego;
    zmq::context_t* contex;

}recursos_juego;

// Metodo para encapsular el documento json en "idObjeto":"XXX","data":"Contenido en Json del objeto"
std::string encapsularJson(std::string jsonEncapsular){
    Json::Value encapsulado;
    Json::FastWriter writer;
}

void enviarObjetoCliente(zmq::socket_t* soc, std::string tipoObjeto, std::string* jsonObjetcString){
  Json::Value enviar;
  Json::FastWriter writer;
  std::string mensaje;

  enviar["idObjeto"] = tipoObjeto;
  enviar["data"] = *jsonObjetcString;

  std::stringstream lineStream(writer.write(enviar));
  std::cout << "Envio..." << writer.write(enviar) << std::endl;
  zmq::message_t request((void*)lineStream.str().c_str(), lineStream.str().size()+1, NULL);
  soc->send (request);
  // Do some work
}

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    std::cout << "-->write_data " << std::endl;
    std::string buf = std::string(static_cast<char *>(ptr), size *nmemb);
    std::stringstream * response = static_cast<std::stringstream *>(stream);
    response->write(buf.c_str(), (std::streamsize)buf.size());
    return size * nmemb;

}

// Permite la ejecución de hilos
void *worker_routine (void *arg)
{
    std::string replyServer;
    Json::Value mensajeCliente;
    Json::Reader readerJson; // Para relizar conversiones de string a objeto Json
    std::string tipoObjeto; // Almacena el tipo de obejto
    std::string data; // 
    std::string tipoObjetoRespuesta; // Se indica el tipo de respuesta que va a dar el servidor
    bool mensajeRecibido = false;
    std::string usuariosConectadosJson; // String para contener la posiciones de los usuarios

    time_t ahora,despues; // Control de actualización de juagdores conectados
    double tiempoSeg = 1000; // Tiempo entre actualizaciones en segundos
    double totalSeg;

    Login log("lixander","123434");

    time(&ahora); // Toma la primera marca de tiempo
    struct recurso_t* contenedor_recursos = (struct recurso_t*) arg;

    zmq::context_t *context = contenedor_recursos->contex;

    zmq::socket_t socket (*context, ZMQ_REP);
    socket.connect ("inproc://workers");

    while (true) {
        // Variable para almacenar el mensaje entrante
        zmq::message_t request;
        //  Espera por algún mensaje de los usuarios
        socket.recv (&request);

        // Conversión de message_t a string
        std::string preJson = std::string(static_cast<char*>(request.data()), request.size()); 

        std::cout << preJson  << std::endl;

        // Se verifica que se realice correctamente la conversion de Json a Objeto Json
        if(!readerJson.parse(preJson,mensajeCliente)) 
        {
            std::cout  << "Error en la conversión de documento Json a Objeto Json\n"
                 << readerJson.getFormattedErrorMessages();
                 // replyServer = "Error formato Json";
        }else {
          // idObjeto contiene la indentificación de qué objeto debemos tratar
          tipoObjeto = mensajeCliente.get("idObjeto", "Not Found" ).asString(); // se obtiene el valor en la clave 'idObjeto'
          data = mensajeCliente.get("data", "Not Found" ).asString(); // se obtiene el valor en la clave 'data'

          if( tipoObjeto == "usuario"){
               Usuario* user = new Usuario(&data); //Se crear el conjeto a partir del Json en formato String
               std::cout << "Usuario " << data << std::endl;
               if(!contenedor_recursos->manejador_juego->conectar(user))
               {
                    replyServer = "Sorry Full server";
               }else{
               // contenedor_recursos->manejador_juego->getUsuarioById(2);
                    replyServer = "Conexión Exitosa";
               }
               tipoObjetoRespuesta = "usuario";

          }else if (tipoObjeto == "ataque"){
              // contenedor_recursos->manejador_juego->atacarUsuario();
              std::cout << "Ataque " << data << std::endl;
              Ataque atac(&data);
              contenedor_recursos->manejador_juego->atacarUsuario(&atac);
              std::cout << "Atacado ..." <<contenedor_recursos->manejador_juego->getUsuarioByIdJson(atac.getIdAtacado()) << std::endl;
              tipoObjetoRespuesta = "ataque";
          }else if (tipoObjeto == "posUsuario"){
              // Cuando el usuario envia su posición se le retorna las posiciones de los demás jugadores en formato Json
              // se crea objeto PosicionUsuario a partir del Json en formato string 
              PosicionUsuario posUser(&data); 
              // Se actuliza la posición del jugador que envia su posición
              contenedor_recursos->manejador_juego->actualizarPosicionUsuario(&posUser);
              // Se obtiene la lista de jugadores conectados en formato Json
              contenedor_recursos->manejador_juego->getUsuariosConectadosJson(&usuariosConectadosJson,posUser.getIdUsuario());
              // La respueta del servidor al usuario que hizo la petición
              replyServer = usuariosConectadosJson; 
              tipoObjetoRespuesta = "posiciones";

          }else if (tipoObjeto == "login"){
              Login logueandose(&data);
              tipoObjetoRespuesta = "login";
              std::string respuestaLogin;
              std::cout << "login " << logueandose.getLoginJson() << std::endl;
              

                                  // Consumo de la API Rest
                                CURL *curl;
                                CURLcode res;    
                                std::string correo = logueandose.getCorreo();
                                std::string contrasena = logueandose.getContrasena();
                                std::string str = "email="+correo+"&password="+contrasena;
                                const char * c = str.c_str();

                                // std::string postFile = "email="+correo+"&password="+contrasena;

                            // don't forget to free the string after finished using it
                                
                                curl_global_init(CURL_GLOBAL_ALL);
                                curl = curl_easy_init();
                                std::stringstream response;
                                if(curl) {
                                      /* First set the URL that is about to receive our POST. This URL can
                                       just as well be a https:// URL if that is what should receive the
                                       data. */ 
                                      curl_easy_setopt(curl, CURLOPT_URL, "https://jobboard-emmanuelhcpk.c9.io/api/v1/sessions");
                                      /* Now specify the POST data */ 
                                      std::cout << "Send post"  << c << std::endl;
                                      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, c);
                                      // std::cout << "------------1-----------"  << std::endl;
                                      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
                                      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
                                      /* Perform the request, res will get the return code */ 
                                      res = curl_easy_perform(curl);
                                      // std::cout << "------------2-----------"  << std::endl;
                                      /* Check for errors */ 
                                      if(res != CURLE_OK)
                                      fprintf(stderr, "curl_easy_perform() failed: %s\n",
                                              curl_easy_strerror(res));

                                      /* always cleanup */ 
                                      curl_easy_cleanup(curl);
                                    }
                                  curl_global_cleanup();
                                  respuestaLogin = response.str();
                                  std::cout << "Get post..."  << respuestaLogin << std::endl;
                                  std::string dato = logueandose.confirmarConexion(&respuestaLogin);
                                  if(dato == "NULL")
                                  {
                                    replyServer == "Error Login";
                                  }else{
                                    Usuario userLogin(&dato);
                                           std::cout << "Usuario conectado se "  << std::endl;
                                           if(!contenedor_recursos->manejador_juego->conectar(&userLogin))
                                           {
                                                replyServer = "Sorry Full server";
                                           }else{
                                           // contenedor_recursos->manejador_juego->getUsuarioById(2);
                                                userLogin.usuarioToJson(&replyServer);
                                           }
                                  }

          }else{
                 std::cout << "Json sin identificacion de Objeto "<< std::endl;
                                  tipoObjetoRespuesta = "error";
                 // replyServer = log.getLoginJson();
                 // std::cout << " log" << replyServer << std::endl;
          }
      }
        // Encapsula el mensaje en 'idObjeto'='','data'='todos los que se quiere enviar'
        enviarObjetoCliente(&socket, tipoObjetoRespuesta, &replyServer);

        std::cout << "Total Conectados: " << contenedor_recursos->manejador_juego->getTotalConectados()<< std::endl;
        // std::cout << "Total Conectados: " << contenedor_recursos->manejador_juego->maximoConectados<< std::endl;
    }
    return (NULL);
}


int main (int argc, char *argv[]) {

// curl_login("eava@gmail.com","12345678");

// std::cout <<  response.str()<< "------------3-----------"  << std::endl;
 //  Prepare our context and socket
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
//////////////////////////////////////////////////////////////
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
