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
        delete nodo->getPaciente();
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

bool ArbolAVL::insertar(Paciente* p) {
    bool insertado = false;
    this->root = insertarRecursivo(this->root, p, insertado);
    return insertado;
}

NodoAVL* ArbolAVL::insertarRecursivo(NodoAVL* nodo, Paciente* p, bool& insertado) {
    if (nodo == nullptr) {
        insertado = true;
        return new NodoAVL(p);
    }

        if (p->getId() < nodo->getPaciente()->getId()) {
        nodo->setLeft(insertarRecursivo(nodo->getLeft(), p, insertado));
    } else if (p->getId() > nodo->getPaciente()->getId()) {
        nodo->setRight(insertarRecursivo(nodo->getRight(), p, insertado));
    } else {
        return nodo;
    }
    return balancear(nodo);
}

Paciente* ArbolAVL::buscarPorID(std::string id, std::string* ruta) {
    if (ruta != nullptr) *ruta = "Root";
    NodoAVL* resultado = buscarRecursivo(this->root, id, ruta);
    if (resultado != nullptr) return resultado->getPaciente();
    return nullptr;
}

NodoAVL* ArbolAVL::buscarRecursivo(NodoAVL* nodo, std::string id, std::string* ruta) {
    if (nodo == nullptr) return nullptr;

    if (nodo->getPaciente()->getId() == id) return nodo;

    if (id < nodo->getPaciente()->getId()) {
        if (ruta != nullptr) *ruta += " -> Izq";
        return buscarRecursivo(nodo->getLeft(), id, ruta);
    } else {
        if (ruta != nullptr) *ruta += " -> Der";
        return buscarRecursivo(nodo->getRight(), id, ruta);
    }
}

Paciente* ArbolAVL::buscarPorNombre(std::string nombre) {
    NodoAVL* resultado = buscarNombreRecursivo(this->root, nombre);
    if (resultado != nullptr) return resultado->getPaciente();
    return nullptr;
}

NodoAVL* ArbolAVL::buscarNombreRecursivo(NodoAVL* nodo, std::string nombre) {
    if (nodo == nullptr) return nullptr;

    if (nodo->getPaciente()->getNombre() == nombre) return nodo;

    NodoAVL* encontradoLeft = buscarNombreRecursivo(nodo->getLeft(), nombre);
    if (encontradoLeft != nullptr) return encontradoLeft;

    return buscarNombreRecursivo(nodo->getRight(), nombre);
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


bool ArbolAVL::estaVacio() const {
    return this->root == nullptr;
}

NodoAVL* ArbolAVL::balancear(NodoAVL* nodo) {
    nodo->setAltura(1 + max(altura(nodo->getLeft()), altura(nodo->getRight())));
    int balance = obtenerBalance(nodo);

    if (balance > 1) {
        if (obtenerBalance(nodo->getLeft()) < 0) {
            nodo->setLeft(rotarLeft(nodo->getLeft()));
        }
        return rotarRight(nodo);
    }

    if (balance < -1) {
        if (obtenerBalance(nodo->getRight()) > 0) {
            nodo->setRight(rotarRight(nodo->getRight()));
        }
        return rotarLeft(nodo);
    }

    return nodo;
}

NodoAVL* ArbolAVL::minimoNodo(NodoAVL* nodo) {
    while (nodo->getLeft() != nullptr) {
        nodo = nodo->getLeft();
    }
    return nodo;
}

NodoAVL* ArbolAVL::quitarMinimo(NodoAVL* nodo) {
    if (nodo->getLeft() == nullptr) {
        NodoAVL* derecho = nodo->getRight();
        delete nodo;
        return derecho;
    }
    nodo->setLeft(quitarMinimo(nodo->getLeft()));
    return balancear(nodo);
}

NodoAVL* ArbolAVL::eliminarRecursivo(NodoAVL* nodo, std::string id, bool& eliminado) {
    if (nodo == nullptr) return nullptr;

    if (id < nodo->getPaciente()->getId()) {
        nodo->setLeft(eliminarRecursivo(nodo->getLeft(), id, eliminado));
    } else if (id > nodo->getPaciente()->getId()) {
        nodo->setRight(eliminarRecursivo(nodo->getRight(), id, eliminado));
    } else {
        eliminado = true;

        if (nodo->getLeft() == nullptr || nodo->getRight() == nullptr) {
            NodoAVL* hijo = (nodo->getLeft() != nullptr) ? nodo->getLeft() : nodo->getRight();
            delete nodo->getPaciente();
            delete nodo;
            return hijo;
        }

        NodoAVL* sucesor = minimoNodo(nodo->getRight());
        delete nodo->getPaciente();
        nodo->setPaciente(sucesor->getPaciente());
        nodo->setRight(quitarMinimo(nodo->getRight()));
    }

    return balancear(nodo);
}

bool ArbolAVL::eliminar(std::string id) {
    bool eliminado = false;
    this->root = eliminarRecursivo(this->root, id, eliminado);
    return eliminado;
}


int ArbolAVL::getAltura() {
    return altura(this->root);
}

int ArbolAVL::getBalanceRaiz() {
    return obtenerBalance(this->root);
}

void ArbolAVL::mostrarFactoresBalance() {
    if (this->root == nullptr) {
        std::cout << "Sin pacientes" << std::endl;
        return;
    }
    balancesRecursivo(this->root);
}

void ArbolAVL::balancesRecursivo(NodoAVL* nodo) {
    if (nodo == nullptr) return;
    std::cout << "ID " << nodo->getPaciente()->getId()
              << " (" << nodo->getPaciente()->getNombre() << ")"
              << " -> altura: " << altura(nodo)
              << " | factor de balance: " << obtenerBalance(nodo) << std::endl;
    balancesRecursivo(nodo->getLeft());
    balancesRecursivo(nodo->getRight());
}


void ArbolAVL::mostrarPreorden() {
    preordenRecursivo(this->root);
}


void ArbolAVL::preordenRecursivo(NodoAVL* nodo) {
    if (nodo != nullptr) {
        std::cout << "ID: " << nodo->getPaciente()->getId()
                  << " | Nombre: " << nodo->getPaciente()->getNombre() << std::endl;
        preordenRecursivo(nodo->getLeft());
        preordenRecursivo(nodo->getRight());
    }
}

void ArbolAVL::mostrarPostorden() {
    postordenRecursivo(this->root);
}


void ArbolAVL::postordenRecursivo(NodoAVL* nodo) {
    if (nodo != nullptr) {
        postordenRecursivo(nodo->getLeft());
        postordenRecursivo(nodo->getRight());
        std::cout << "ID: " << nodo->getPaciente()->getId()
                  << " | Nombre: " << nodo->getPaciente()->getNombre() << std::endl;
    }
}