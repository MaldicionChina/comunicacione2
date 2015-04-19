#include "Posicion.hpp"
class PosicionUsuario : public Posicion {
    private:
        int usuario_id;
    
   
    public:
    PosicionUsuario(double* lat,double* lon ,int* id ); 
    
    };