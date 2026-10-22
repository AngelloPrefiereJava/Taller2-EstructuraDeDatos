#include "NodoAVL.h"

NodoAVL::NodoAVL(Paciente* p) {
    this->paciente = p;
    this->left = nullptr;
    this->right = nullptr;
    this->altura = 1; 
}

Paciente* NodoAVL::getPaciente() const { return this->paciente; }
NodoAVL* NodoAVL::getLeft() const { return this->left; }
NodoAVL* NodoAVL::getRight() const { return this->right; }
int NodoAVL::getAltura() const { return this->altura; }

void NodoAVL::setLeft(NodoAVL* nodo) { this->left = nodo; }
void NodoAVL::setRight(NodoAVL* nodo) { this->right = nodo; }
void NodoAVL::setAltura(int h) { this->altura = h; }