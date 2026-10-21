#include "Arbol.h"

Arbol::Arbol(){
    this->root = nullptr;
    this->armarArbol();
}

Arbol::Arbol(){
    destruirRecursivo(this->root);
}

void Arbol::destruirRecursivo(NodoArbol* nodo) {
    if (nodo != nullptr) {
        destruirRecursivo(nodo->getLeft());
        destruirRecursivo(nodo->getRight());
        delete nodo;
    }
}

void Arbol::armarArbol(){

    NodoArbol* pediatria = new NodoArbol("", "Pediatria");
    NodoArbol* cirugia = new NodoArbol("", "Cirugia");
    NodoArbol* traumatologia = new NodoArbol("", "Traumatologia");
    NodoArbol* neurologia = new NodoArbol("", "Neurologia");
    NodoArbol* cardiologia = new NodoArbol("", "Cardiologia");
    NodoArbol* urgencias = new NodoArbol("", "Urgencias");
    NodoArbol* hospitalizacion = new NodoArbol("", "Hospitalizacion");
    NodoArbol* medicinaGeneral = new NodoArbol("", "Medicina General");

    NodoArbol* pregDias = new NodoArbol("DIAS_HOSP_>=_2", "");
    pregDias->setLeft(hospitalizacion); 
    pregDias->setRight(medicinaGeneral);

    NodoArbol* pregTemperaturaDolor = new NodoArbol("TEMP_>_38.5_O_DOLOR_>=_8", "");
    pregTemperaturaDolor->setLeft(urgencias);
    pregTemperaturaDolor->setRight(pregDias);

    NodoArbol* pregTipoDolor = new NodoArbol("TIPO_DOLOR_==_PECHO", "");
    pregTipoDolor->setLeft(cardiologia);
    pregTipoDolor->setRight(pregTemperaturaDolor);

    NodoArbol* pregSintomas = new NodoArbol("SINTOMAS_NEUROLOGICOS_==_1", "");
    pregSintomas->setLeft(neurologia);
    pregSintomas->setRight(pregTipoDolor);


    NodoArbol* pregCirugia = new NodoArbol("REQUIERE_CIRUGIA_==_1", "");
    pregCirugia->setLeft(cirugia);
    pregCirugia->setRight(traumatologia);

    NodoArbol* pregTrauma = new NodoArbol("TRAUMA_==_1", "");
    pregTrauma->setLeft(pregCirugia);
    pregTrauma->setRight(pregSintomas);


    this->root = new NodoArbol("EDAD_<_14", "");
    this->root->setLeft(pediatria);
    this->root->setRight(pregTrauma);
}

std::string Arbol::clasificarPaciente(Paciente* p) {
    if (this->root == nullptr) return "Error";
    return evaluarRecursivo(this->root, p);
}

std::string Arbol::evaluarRecursivo(NodoArbol* nodo, Paciente* p) {

    if (nodo->esServicio()) {
        return nodo->getServicio();
    }

    std::string cond = nodo->getCondicion();

    if (cond == "EDAD_<_14") {
        if (p->getEdad() < 14){ return evaluarRecursivo(nodo->getLeft(), p);}
        else {return evaluarRecursivo(nodo->getRight(), p);}
    }
    else if (cond == "TRAUMA_==_1") {
        if (p->getTrauma() == 1) {return evaluarRecursivo(nodo->getLeft(), p);}
        else {return evaluarRecursivo(nodo->getRight(), p);}
    }
    else if (cond == "REQUIERE_CIRUGIA_==_1") {
        if (p->getRequiereCirugia() == 1) {return evaluarRecursivo(nodo->getLeft(), p);}
        else {return evaluarRecursivo(nodo->getRight(), p);}
    }
    else if (cond == "SINTOMAS_NEUROLOGICOS_==_1") {
        if (p->getSintomasNeurologicos() == 1) {return evaluarRecursivo(nodo->getLeft(), p);}
        else {return evaluarRecursivo(nodo->getRight(), p);}
    }
    else if (cond == "TIPO_DOLOR_==_PECHO") {
        if (p->getTipoDolor() == "pecho") {return evaluarRecursivo(nodo->getLeft(), p);}
        else {return evaluarRecursivo(nodo->getRight(), p);}
    }
    else if (cond == "TEMP_>_38.5_O_DOLOR_>=_8") {
        if (p->getTemperatura() > 38.5f || p->getDolor() >= 8) {return evaluarRecursivo(nodo->getLeft(), p);}
        else {return evaluarRecursivo(nodo->getRight(), p);}
    }
    else if (cond == "DIAS_HOSP_>=_2") {
        if (p->getDiasHospitalizacion() >= 2) {return evaluarRecursivo(nodo->getLeft(), p);}
        else {return evaluarRecursivo(nodo->getRight(), p);}
    }

    return "Desconocido";
}

