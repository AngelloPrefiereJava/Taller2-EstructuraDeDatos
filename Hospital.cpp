#include "Hospital.h"
#include <iostream>
#include <fstream>

const int NUM_CAMPOS = 11;

static int separar(const std::string& linea, std::string campos[]) {
    int cantidad = 0;
    std::string actual;
    for (size_t i = 0; i < linea.size(); i++) {
        if (linea[i] == ';') {
            if (cantidad < NUM_CAMPOS) campos[cantidad] = actual;
            cantidad++;
            actual.clear();
        } else {
            actual += linea[i];
        }
    }
    if (cantidad < NUM_CAMPOS) campos[cantidad] = actual;
    cantidad++;
    return cantidad;
}

static bool aEntero(const std::string& s, int& salida) {
    try {
        size_t pos;
        salida = std::stoi(s, &pos);
        return pos == s.size();
    } catch (...) {
        return false;
    }
}

static bool aDecimal(const std::string& s, float& salida) {
    try {
        size_t pos;
        salida = std::stof(s, &pos);
        return pos == s.size();
    } catch (...) {
        return false;
    }
}

Hospital::Hospital() {
    this->nombres[0] = "Urgencias";
    this->nombres[1] = "Medicina General";
    this->nombres[2] = "Traumatologia";
    this->nombres[3] = "Cardiologia";
    this->nombres[4] = "Neurologia";
    this->nombres[5] = "Cirugia";
    this->nombres[6] = "Pediatria";
    this->nombres[7] = "Hospitalizacion";
}

int Hospital::indiceServicio(const std::string& servicio) const {
    for (int i = 0; i < NUM_SERVICIOS; i++) {
        if (this->nombres[i] == servicio) return i;
    }
    return -1;
}

int Hospital::cargarDesdeArchivo(const std::string& ruta) {
    std::ifstream archivo(ruta);
    if (!archivo.is_open()) {
        std::cout << "Error: no se pudo abrir '" << ruta << "'." << std::endl;
        return -1;
    }

    std::string linea;
    int numLinea = 0;
    int cargados = 0;
    const int MAX_IDS = 1000;
    std::string idsVistos[MAX_IDS];
    int totalIds = 0;
    while (std::getline(archivo, linea)) {
        numLinea++;
        if (linea.empty()) continue;

        std::string c[NUM_CAMPOS];
        int cantidad = separar(linea, c);
        if (cantidad != NUM_CAMPOS) {
            std::cout << "Linea " << numLinea << " rechazada: faltan o sobran campos." << std::endl;
            continue;
        }

        int edad, dolor, trauma, neuro, cirugia, dias;
        float temp, presion;
        bool ok = aEntero(c[2], edad) && aDecimal(c[3], temp) && aDecimal(c[4], presion)
               && aEntero(c[5], dolor) && aEntero(c[7], trauma) && aEntero(c[8], neuro)
               && aEntero(c[9], cirugia) && aEntero(c[10], dias);

        if (!ok) {
            std::cout << "Linea " << numLinea << " rechazada: campo numerico invalido." << std::endl;
            continue;
        }

        Paciente* p = new Paciente(c[0], c[1], edad, temp, presion, dolor, c[6],
                           trauma, neuro, cirugia, dias);

    std::string motivo;
    if (!Arbol::datosValidos(p, motivo)) {
            std::cout << "Linea " << numLinea << " rechazada: " << motivo << "." << std::endl;
            delete p;
            continue;
        }

        this->cola.push(p);
        cargados++;
    }

    std::cout << cargados << " paciente(s) en cola." << std::endl;
    return cargados;
}

void Hospital::atenderPacientes() {
    if (this->cola.isEmpty()) {
        std::cout << "No hay pacientes en espera." << std::endl;
        return;
    }

    while (!this->cola.isEmpty()) {
        Paciente* p = this->cola.pop();

        std::string servicio = this->arbolDecision.clasificarPaciente(p);
        int indice = indiceServicio(servicio);

        std::cout << "ID: " << p->getId() << " | " << p->getNombre() << std::endl;

        if (indice < 0) {
            std::cout << "No se pudo asignar servicio (" << servicio << "). Paciente descartado." << std::endl;
            delete p;
        } else {
            std::cout << "Servicio asignado: " << servicio << std::endl;
            this->avl[indice].insertar(p);
        }
        std::cout << "-------------------" << std::endl;
    }
}