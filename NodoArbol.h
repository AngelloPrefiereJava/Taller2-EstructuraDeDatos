#ifndef NODOARBOL_H
#define NODOARBOL_H

#include <string>

class NodoArbol{
    private:
        NodoArbol* left;
        NodoArbol* right;
        std::string condicion,servicio;
    public:
        NodoArbol(std::string condicion,std::string servicio);

        NodoArbol* getLeft() const;
        NodoArbol* getRight() const;
        std::string getCondicion() const;
        std::string getServicio() const;

        void setRight(NodoArbol* nodo);
        void setLeft(NodoArbol* nodo);

        bool esServicio();
};

#endif