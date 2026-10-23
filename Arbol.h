#ifndef ARBOL_H
#define ARBOL_H

#include "NodoArbol.h"
#include "Paciente.h"
class Arbol{
private:
    NodoArbol* root;

    std::string evaluarRecursivo(NodoArbol* nodo, Paciente* p);

    void destruirRecursivo(NodoArbol* nodo);
public:

    Arbol();
    ~Arbol();

    void armarArbol();
    std::string clasificarPaciente(Paciente* p);
    static bool datosValidos(Paciente* p, std::string& motivo);
};
#endif