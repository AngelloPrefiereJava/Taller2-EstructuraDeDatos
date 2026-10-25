#ifndef ARBOL_H
#define ARBOL_H

#include "NodoArbol.h"
#include "Paciente.h"
class Arbol{
private:
    NodoArbol* root;

    std::string evaluarRecursivo(NodoArbol* nodo, Paciente* p, std::string& ruta);

    void destruirRecursivo(NodoArbol* nodo);
    void imprimirNodo(NodoArbol* nodo, int nivel);
    void preordenRecursivo(NodoArbol* nodo, int nivel);
    void inordenRecursivo(NodoArbol* nodo, int nivel);
    void postordenRecursivo(NodoArbol* nodo, int nivel);
public:

    Arbol();
    ~Arbol();

    void armarArbol();
    std::string clasificarPaciente(Paciente* p);
    static bool datosValidos(Paciente* p, std::string& motivo);
    std::string clasificarPaciente(Paciente* p, std::string& ruta);
    void mostrarPreorden();
    void mostrarInorden();
    void mostrarPostorden();
};
#endif