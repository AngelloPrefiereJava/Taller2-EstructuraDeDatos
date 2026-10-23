#ifndef NODO_AVL_H
#define NODO_AVL_H

#include "Paciente.h"

class NodoAVL {
private:
    Paciente* paciente;
    NodoAVL* left;
    NodoAVL* right;
    int altura;

public:
    NodoAVL(Paciente* p);

    Paciente* getPaciente() const;
    NodoAVL* getLeft() const;
    NodoAVL* getRight() const;
    int getAltura() const;

    void setLeft(NodoAVL* nodo);
    void setRight(NodoAVL* nodo);
    void setAltura(int h);
    void setPaciente(Paciente* p);
};

#endif