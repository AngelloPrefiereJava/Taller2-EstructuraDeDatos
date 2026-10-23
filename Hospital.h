#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <string>
#include "Queue.h"
#include "Arbol.h"
#include "ArbolAVL.h"
#include "Paciente.h"

class Hospital {
private:
    static const int NUM_SERVICIOS = 8;

    Queue cola;                        
    Arbol arbolDecision;                 
    std::string nombres[NUM_SERVICIOS];  
    ArbolAVL avl[NUM_SERVICIOS];         

    int indiceServicio(const std::string& servicio) const;

public:
    Hospital();
    int cargarDesdeArchivo(const std::string& ruta);
    void atenderPacientes();
};

#endif