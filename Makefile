
LIB:=./lib
SRC:=./src
INC:=./include
BIN:=./bin
SHELL := /bin/sh
LIBS:= -L$(LIB) -lzmq -lUsuario -lJson -lPosicion -lPosicionUsuario
INCLUDE:= -I$(INC)
EXPORT_PATH:=
CC:= g++ -std=c++11 

#target: dependencies
#[tab] system command

# $@ -> reemplaza por el nombre de la regla(target)
# $< -> reemplaza por el nombre de la primera dependencia
#%.o:%.c
#	$(CC) -c $< -o $@

all: makeLibs serverZMQ clientZMQ ./exportar_lib_path
	@./export_lib_path.sh 

serverZMQ: $(SRC)/serverZeroMQ.cpp makeLibs
	$(CC) $(INCLUDE) $< -o $(BIN)/$@ $(LIBS)

# Se compila el progrema cliente	
clientZMQ: $(SRC)/clientZeroMQ.cpp makeLibs
	$(CC) $(INCLUDE) $< -o $(BIN)/$@ $(LIBS)

makeLibs: libPosicion.o libPosicionUsuario.o  libUsuario.o libJson.o libPosicion.so libPosicionUsuario.so libUsuario.so libJson.so

#Como se usa una libería compartida y no se encuentra en los paths
#estandar en necesario esportar la variable de entorno LD_LIBRARY_PATH
#con el path donde están las librerías ya compiladas
exportar_lib_path: ./export_lib_path.sh 
	@./export_lib_path.sh 
##############################Shared Library Usuario######################################
# Se crea el  codigio objeto para la librería
libUsuario.o: $(SRC)/Usuario.cpp $(INC)/Usuario.hpp
	$(CC) $(INCLUDE) -c -fPIC $< -o $(LIB)/$@ 

#Se coge el codigo objeto y se compila para que sea una libreria compartida
libUsuario.so: $(LIB)/libUsuario.o libUsuario.o
	$(CC) -shared $<  -o $(LIB)/$@
##############################Shared Library Usuario######################################

##############################Shared Library Json#########################################
libJson.o: $(SRC)/jsoncpp.cpp $(INC)/json/json.h
	$(CC) $(INCLUDE) -c -fPIC $< -o $(LIB)/$@ 

libJson.so: $(LIB)/libJson.o libJson.o
	$(CC) -shared $<  -o $(LIB)/$@
##############################Shared Library Json#########################################

##############################Shared Library Posicion######################################
libPosicion.o: $(SRC)/Posicion.cpp $(INC)/Posicion.hpp
	$(CC) $(INCLUDE) -c -fPIC $< -o $(LIB)/$@ 

libPosicion.so: $(LIB)/libPosicion.o libPosicion.o
	$(CC) -shared $<  -o $(LIB)/$@

##############################Shared Library Posicion######################################

##############################Shared Library PosicionUsuario######################################
libPosicionUsuario.o: $(SRC)/PosicionUsuario.cpp $(INC)/PosicionUsuario.hpp
	$(CC) $(INCLUDE) -c -fPIC $< -o $(LIB)/$@

libPosicionUsuario.so: $(LIB)/libPosicionUsuario.o libPosicionUsuario.o
	$(CC) -shared $<  -o $(LIB)/$@ 

##############################Shared Library PosicionUsuario######################################

clean: 
	rm -f $(LIB)/*.o 
	rm -f $(LIB)/*.so 
	rm -f $(BIN)/*

#.PHONY: libUsuario.so libUsuario.o clientZMQ serverZMQ exportar_lib_paht libJson.so libJson.o