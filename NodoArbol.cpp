#include "NodoArbol.h"

NodoArbol::NodoArbol(std::string condicion, std::string servicio){
    this->condicion = condicion;
    this->servicio = servicio;
    this->left = nullptr;
    this->right = nullptr;
}

NodoArbol* NodoArbol::getRight()const{
    return this->right;
}

void NodoArbol::setRight(NodoArbol* nodo){
    this->right = nodo;
}

void NodoArbol::setLeft(NodoArbol* nodo){
    this->left = nodo;
}

NodoArbol* NodoArbol::getLeft()const{
    return this->left;
}

std::string NodoArbol::getServicio() const{
    return this->servicio;
}

std::string NodoArbol::getCondicion() const{
    return this->condicion;
}

bool NodoArbol::esServicio(){
    return(this->left == nullptr && this->right == nullptr);
}