#include "ArbolAVL.h"

ArbolAVL::ArbolAVL() {
    this->root = nullptr;
}

ArbolAVL::~ArbolAVL() {
    destruirRecursivo(this->root);
}

void ArbolAVL::destruirRecursivo(NodoAVL* nodo) {
    if (nodo != nullptr) {
        destruirRecursivo(nodo->getLeft());
        destruirRecursivo(nodo->getRight());
        delete nodo; 
    }
}

int ArbolAVL::max(int a, int b) {
    return (a > b) ? a : b;
}

int ArbolAVL::altura(NodoAVL* nodo) {
    if (nodo == nullptr) return 0;
    return nodo->getAltura();
}

int ArbolAVL::obtenerBalance(NodoAVL* nodo) {
    if (nodo == nullptr) return 0;
    return altura(nodo->getLeft()) - altura(nodo->getRight());
}

NodoAVL* ArbolAVL::rotarRight(NodoAVL* y) {
    NodoAVL* x = y->getLeft();
    NodoAVL* T2 = x->getRight();

    x->setRight(y);
    y->setLeft(T2);

    y->setAltura(max(altura(y->getLeft()), altura(y->getRight())) + 1);
    x->setAltura(max(altura(x->getLeft()), altura(x->getRight())) + 1);

    return x;
}

NodoAVL* ArbolAVL::rotarLeft(NodoAVL* x) {
    NodoAVL* y = x->getRight();
    NodoAVL* T2 = y->getLeft();

    y->setLeft(x);
    x->setRight(T2);

    x->setAltura(max(altura(x->getLeft()), altura(x->getRight())) + 1);
    y->setAltura(max(altura(y->getLeft()), altura(y->getRight())) + 1);

    return y;
}

void ArbolAVL::insertar(Paciente* p) {
    this->root = insertarRecursivo(this->root, p);
}

NodoAVL* ArbolAVL::insertarRecursivo(NodoAVL* nodo, Paciente* p) {
    if (nodo == nullptr) {
        return new NodoAVL(p);
    }

    if (p->getEdad() < nodo->getPaciente()->getEdad()) {
        nodo->setLeft(insertarRecursivo(nodo->getLeft(), p));
    } else if (p->getEdad() >= nodo->getPaciente()->getEdad()) { 
        nodo->setRight(insertarRecursivo(nodo->getRight(), p));
    }

    nodo->setAltura(1 + max(altura(nodo->getLeft()), altura(nodo->getRight())));
    int balance = obtenerBalance(nodo);

    if (balance > 1 && p->getEdad() < nodo->getLeft()->getPaciente()->getEdad())
        return rotarRight(nodo);

    if (balance < -1 && p->getEdad() >= nodo->getRight()->getPaciente()->getEdad())
        return rotarLeft(nodo);

    if (balance > 1 && p->getEdad() >= nodo->getLeft()->getPaciente()->getEdad()) {
        nodo->setLeft(rotarLeft(nodo->getLeft()));
        return rotarRight(nodo);
    }

    if (balance < -1 && p->getEdad() < nodo->getRight()->getPaciente()->getEdad()) {
        nodo->setRight(rotarRight(nodo->getRight()));
        return rotarLeft(nodo);
    }

    return nodo;
}

Paciente* ArbolAVL::buscarPorID(std::string id) {
    NodoAVL* resultado = buscarRecursivo(this->root, id);
    if (resultado != nullptr) return resultado->getPaciente();
    return nullptr;
}

NodoAVL* ArbolAVL::buscarRecursivo(NodoAVL* nodo, std::string id) {
    if (nodo == nullptr || nodo->getPaciente()->getId() == id)
        return nodo;

    if (nodo->getPaciente()->getId() < id)
        return buscarRecursivo(nodo->getRight(), id);

    return buscarRecursivo(nodo->getLeft(), id);
}

void ArbolAVL::mostrarInorden() {
    inordenRecursivo(this->root);
}

void ArbolAVL::inordenRecursivo(NodoAVL* nodo) {
    if (nodo != nullptr) {
        inordenRecursivo(nodo->getLeft());
        std::cout << "ID: " << nodo->getPaciente()->getId() 
                  << " | Nombre: " << nodo->getPaciente()->getNombre() << std::endl;
        inordenRecursivo(nodo->getRight());
    }
}