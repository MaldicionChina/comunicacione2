
LIB:=./lib
SRC:=./src
INC:=./include
BIN:=./bin
SHELL := /bin/sh
LIBS:= -L$(LIB) -lzmq -lJugador 
INCLUDE:= -I$(INC)
EXPORT_PATH:=
CC:= g++ -std=c++11 

#target: dependencies
#[tab] system command

# $@ -> reemplaza por el nombre de la regla(target)
# $< -> reemplaza por el nombre de la primera dependencia
#%.o:%.c
#	$(CC) -c $< -o $@

all: serverZMQ 

serverZMQ: $(SRC)/serverZeroMQ.cpp
	$(CC) $< -o $@ $(LIBS)

# Se compila el progrema cliente	
clientZMQ: $(SRC)/clientZeroMQ.cpp libJugador.o libJugador.so
	$(CC) $(INCLUDE) $< -o $(BIN)/$@ $(LIBS)


#Como se usa una libería compartida y no se encuentra en los paths
#estandar en necesario esportar la variable de entorno LD_LIBRARY_PATH
#con el path donde están las librerías ya compiladas
exportar_lib_path: ./export_lib_path.sh 
	@./export_lib_path.sh 

# Se crea el  codigio objeto para la librería
libJugador.o: $(SRC)/Jugador.cpp ./include/Jugador.hpp
	$(CC) $(INCLUDE) -c -fPIC $< -o $(LIB)/$@ 

#Se coge el codigo objeto y se compila para que sea una libreria compartida
libJugador.so: $(LIB)/libJugador.o libJugador.o
	$(CC) -shared $<  -o $(LIB)/$@

clean: serverZMQ
	rm -f $(LIB)/*.o 
	rm -f $(LIB)/*.so 

.PHONY: libJugador.so libJugador.o clientZMQ serverZMQ exportar_lib_paht 
