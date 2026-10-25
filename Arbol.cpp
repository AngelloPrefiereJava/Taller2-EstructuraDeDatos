#include "Arbol.h"
#include <iostream>

Arbol::Arbol(){
    this->root = nullptr;
    this->armarArbol();
}

Arbol::~Arbol(){
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

static std::string aMinusculas(const std::string& s);

static void agregarRuta(std::string& ruta, const std::string& texto) {
    if (ruta != "") ruta += " -> ";
    ruta += texto;
}

std::string Arbol::clasificarPaciente(Paciente* p) {
    std::string ruta;
    return clasificarPaciente(p, ruta);
}

std::string Arbol::clasificarPaciente(Paciente* p, std::string& ruta) {
    ruta = "";
    if (this->root == nullptr) return "Error";
    return evaluarRecursivo(this->root, p, ruta);
}

std::string Arbol::evaluarRecursivo(NodoArbol* nodo, Paciente* p, std::string& ruta) {
    if (nodo->esServicio()) {
        return nodo->getServicio();
    }

    std::string cond = nodo->getCondicion();
    bool cumple;
    std::string textoSi, textoNo;

    if (cond == "EDAD_<_14") {
        cumple = (p->getEdad() < 14);
        textoSi = "Edad < 14";
        textoNo = "Edad >= 14";
    }
    else if (cond == "TRAUMA_==_1") {
        cumple = (p->getTrauma() == 1);
        textoSi = "Trauma == 1";
        textoNo = "Trauma == 0";
    }
    else if (cond == "REQUIERE_CIRUGIA_==_1") {
        cumple = (p->getRequiereCirugia() == 1);
        textoSi = "RequiereCirugia == 1";
        textoNo = "RequiereCirugia == 0";
    }
    else if (cond == "SINTOMAS_NEUROLOGICOS_==_1") {
        cumple = (p->getSintomasNeurologicos() == 1);
        textoSi = "SintomasNeurologicos == 1";
        textoNo = "SintomasNeurologicos == 0";
    }
    else if (cond == "TIPO_DOLOR_==_PECHO") {
        cumple = (aMinusculas(p->getTipoDolor()) == "pecho");
        textoSi = "TipoDolor == pecho";
        textoNo = "TipoDolor != pecho";
    }
    else if (cond == "TEMP_>_38.5_O_DOLOR_>=_8") {
        cumple = (p->getTemperatura() > 38.5f || p->getDolor() >= 8);
        textoSi = "Temperatura > 38.5 o Dolor >= 8";
        textoNo = "Temperatura <= 38.5 y Dolor < 8";
    }
    else if (cond == "DIAS_HOSP_>=_2") {
        cumple = (p->getDiasHospitalizacion() >= 2);
        textoSi = "DiasHospitalizacion >= 2";
        textoNo = "DiasHospitalizacion < 2";
    }
    else {
        return "Desconocido";
    }

    if (cumple) {
        agregarRuta(ruta, textoSi);
        return evaluarRecursivo(nodo->getLeft(), p, ruta);
    }
    agregarRuta(ruta, textoNo);
    return evaluarRecursivo(nodo->getRight(), p, ruta);
}

static std::string aMinusculas(const std::string& s) {
    std::string r = s;
    for (size_t i = 0; i < r.size(); i++) {
        if (r[i] >= 'A' && r[i] <= 'Z') {
            r[i] = r[i] + 32;
        }
    }
    return r;
}

bool Arbol::datosValidos(Paciente* p, std::string& motivo) {
    if (p->getId().empty()) { motivo = "ID vacio"; return false; }
    if (p->getNombre().empty()) { motivo = "nombre vacio"; return false; }
    if (p->getEdad() < 0 || p->getEdad() > 120) { motivo = "edad fuera de rango (0-120)"; return false; }
    if (p->getTemperatura() < 30 || p->getTemperatura() > 45) { motivo = "temperatura fuera de rango (30-45)"; return false; }
    if (p->getPresionArterial() < 40 || p->getPresionArterial() > 300) { motivo = "presion fuera de rango (40-300)"; return false; }
    if (p->getDolor() < 0 || p->getDolor() > 10) { motivo = "dolor fuera de rango (0-10)"; return false; }

    std::string tipo = aMinusculas(p->getTipoDolor());
    if (tipo != "pecho" && tipo != "cabeza" && tipo != "abdomen" && tipo != "extremidad" && tipo != "otro") {
        motivo = "tipo de dolor desconocido";
        return false;
    }

    if (p->getTrauma() != 0 && p->getTrauma() != 1) { motivo = "Trauma debe ser 0 o 1"; return false; }
    if (p->getSintomasNeurologicos() != 0 && p->getSintomasNeurologicos() != 1) { motivo = "SintomasNeurologicos debe ser 0 o 1"; return false; }
    if (p->getRequiereCirugia() != 0 && p->getRequiereCirugia() != 1) { motivo = "RequiereCirugia debe ser 0 o 1"; return false; }
    if (p->getDiasHospitalizacion() < 0 || p->getDiasHospitalizacion() > 365) { motivo = "dias de hospitalizacion fuera de rango (0-365)"; return false; }

    return true;
}


void Arbol::imprimirNodo(NodoArbol* nodo, int nivel) {
    for (int i = 0; i < nivel; i++) std::cout << "    ";
    if (nodo->esServicio()) std::cout << "[Servicio: " << nodo->getServicio() << "]" << std::endl;
    else std::cout << nodo->getCondicion() << std::endl;
}

void Arbol::mostrarPreorden() { preordenRecursivo(this->root, 0); }
void Arbol::mostrarInorden() { inordenRecursivo(this->root, 0); }
void Arbol::mostrarPostorden() { postordenRecursivo(this->root, 0); }

void Arbol::preordenRecursivo(NodoArbol* nodo, int nivel) {
    if (nodo == nullptr) return;
    imprimirNodo(nodo, nivel);
    preordenRecursivo(nodo->getLeft(), nivel + 1);
    preordenRecursivo(nodo->getRight(), nivel + 1);
}

void Arbol::inordenRecursivo(NodoArbol* nodo, int nivel) {
    if (nodo == nullptr) return;
    inordenRecursivo(nodo->getLeft(), nivel + 1);
    imprimirNodo(nodo, nivel);
    inordenRecursivo(nodo->getRight(), nivel + 1);
}

void Arbol::postordenRecursivo(NodoArbol* nodo, int nivel) {
    if (nodo == nullptr) return;
    postordenRecursivo(nodo->getLeft(), nivel + 1);
    postordenRecursivo(nodo->getRight(), nivel + 1);
    imprimirNodo(nodo, nivel);
}

