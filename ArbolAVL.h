#ifndef ARBOL_AVL_H
#define ARBOL_AVL_H

#include "NodoAVL.h"
#include <string>
#include <iostream>

class ArbolAVL {
private:
    NodoAVL* root;

    int altura(NodoAVL* nodo);
    int obtenerBalance(NodoAVL* nodo);
    int max(int a, int b);

    NodoAVL* rotarRight(NodoAVL* y);
    NodoAVL* rotarLeft(NodoAVL* x);
    
    NodoAVL* insertarRecursivo(NodoAVL* nodo, Paciente* p);
    NodoAVL* buscarRecursivo(NodoAVL* nodo, std::string id);
    void destruirRecursivo(NodoAVL* nodo);
    void inordenRecursivo(NodoAVL* nodo);

public:
    ArbolAVL();
    ~ArbolAVL();

    void insertar(Paciente* p);
    Paciente* buscarPorID(std::string id);
    void mostrarInorden();
};

#endif