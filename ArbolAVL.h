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
    
    NodoAVL* insertarRecursivo(NodoAVL* nodo, Paciente* p, bool& insertado);
    NodoAVL* buscarRecursivo(NodoAVL* nodo, std::string id, std::string* ruta);
    NodoAVL* buscarNombreRecursivo(NodoAVL* nodo, std::string nombre);
    void destruirRecursivo(NodoAVL* nodo);
    

    void inordenRecursivo(NodoAVL* nodo);
    void preordenRecursivo(NodoAVL* nodo);
    void postordenRecursivo(NodoAVL* nodo);

    NodoAVL* balancear(NodoAVL* nodo);
    NodoAVL* minimoNodo(NodoAVL* nodo);
    NodoAVL* quitarMinimo(NodoAVL* nodo);
    NodoAVL* eliminarRecursivo(NodoAVL* nodo, std::string id, bool& eliminado);
    void balancesRecursivo(NodoAVL* nodo);

public:
    ArbolAVL();
    ~ArbolAVL();

    bool insertar(Paciente* p);
    Paciente* buscarPorID(std::string id, std::string* ruta = nullptr);
    Paciente* buscarPorNombre(std::string nombre);

    void mostrarInorden();
    void mostrarPreorden();
    void mostrarPostorden(); 

    bool estaVacio() const;
    bool eliminar(std::string id);
    int getAltura();
    int getBalanceRaiz();
    void mostrarFactoresBalance();
};

#endif