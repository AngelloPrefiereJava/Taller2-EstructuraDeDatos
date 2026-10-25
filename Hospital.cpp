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
        
                bool duplicado = false;
        for (int i = 0; i < totalIds; i++) {
            if (idsVistos[i] == p->getId()) {
                duplicado = true;
                break;
            }
        }
        if (duplicado) {
            std::cout << "Linea " << numLinea << " rechazada: ID duplicado (" << p->getId() << ")." << std::endl;
            delete p;
            continue;
        }

        if (totalIds >= MAX_IDS) {
            std::cout << "Linea " << numLinea << " rechazada: se alcanzo el maximo de " << MAX_IDS << " pacientes." << std::endl;
            delete p;
            continue;
        }
        idsVistos[totalIds] = p->getId();
        totalIds++;

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

        std::string ruta;
        std::string servicio = this->arbolDecision.clasificarPaciente(p, ruta);
        int indice = indiceServicio(servicio);

        std::cout << "ID: " << p->getId() << " | " << p->getNombre() << std::endl;
        std::cout << "Ruta: " << ruta << std::endl;

        if (indice < 0) {
            std::cout << "No se pudo asignar servicio (" << servicio << "). Paciente descartado." << std::endl;
            delete p;
        } else {
            std::cout << "Servicio asignado: " << servicio << std::endl;
                        if (!this->avl[indice].insertar(p)) {
                std::cout << "Error: el ID " << p->getId() << " ya existe en " << servicio
                          << ". Paciente descartado." << std::endl;
                delete p;
            }
        }
        std::cout << "-------------------" << std::endl;
    }
}


void Hospital::verDepartamentos() {
    std::cout << "\n=== DEPARTAMENTOS ===" << std::endl;

    for (int i = 0; i < NUM_SERVICIOS; i++) {
        std::cout << "\n" << this->nombres[i] << std::endl;
        if (this->avl[i].estaVacio()) {
            std::cout << "Sin pacientes" << std::endl;
        } else {
             std::cout << "Altura: " << this->avl[i].getAltura() << " | Factor de balance de la raiz: " << this->avl[i].getBalanceRaiz() << std::endl;
            std::cout << "-- Inorden --" << std::endl;
            this->avl[i].mostrarInorden();
            std::cout << "-- Preorden --" << std::endl;
            this->avl[i].mostrarPreorden();
            std::cout << "-- Postorden --" << std::endl;
            this->avl[i].mostrarPostorden();
            std::cout << "-- Altura y balance por nodo --" << std::endl;
            this->avl[i].mostrarFactoresBalance();
        }
    }
}


void Hospital::buscarPaciente() {
    std::cout << "Indique el ID o Nombre del paciente: ";
    std::string clave;
    std::getline(std::cin, clave);

    std::cout << "Buscando en AVL..." << std::endl;

    for (int i = 0; i < NUM_SERVICIOS; i++) {
        std::string ruta;
        Paciente* p = this->avl[i].buscarPorID(clave, &ruta);
        if (p != nullptr) {
            std::cout << "Paciente encontrado:" << std::endl;
            std::cout << "ID: " << p->getId() << " | Nombre: " << p->getNombre()
                      << " | Edad: " << p->getEdad() << std::endl;
            std::cout << "Departamento: " << this->nombres[i] << std::endl;
            std::cout << "Ruta de busqueda: " << ruta << std::endl;
            return;
        }
    }

    for (int i = 0; i < NUM_SERVICIOS; i++) {
        Paciente* p = this->avl[i].buscarPorNombre(clave);
        if (p != nullptr) {
            std::cout << "Paciente encontrado:" << std::endl;
            std::cout << "ID: " << p->getId() << " | Nombre: " << p->getNombre()
                      << " | Edad: " << p->getEdad() << std::endl;
            std::cout << "Departamento: " << this->nombres[i] << std::endl;
            std::cout << "Ruta de busqueda: busqueda por nombre (recorrido del AVL)" << std::endl;
            return;
        }
    }

    std::cout << "Paciente no encontrado." << std::endl;
}

void Hospital::eliminarPaciente() {
    std::cout << "Indique el ID del paciente a eliminar: ";
    std::string id;
    std::getline(std::cin, id);

    for (int i = 0; i < NUM_SERVICIOS; i++) {
        if (this->avl[i].buscarPorID(id) != nullptr) {
            this->avl[i].eliminar(id);
            std::cout << "Paciente " << id << " eliminado de " << this->nombres[i] << "." << std::endl;
            return;
        }
    }
    std::cout << "No existe un paciente con ID " << id << "." << std::endl;
}

void Hospital::verArbolDecision() {
    std::cout << "\n-- Preorden --" << std::endl;
    this->arbolDecision.mostrarPreorden();
    std::cout << "\n-- Inorden --" << std::endl;
    this->arbolDecision.mostrarInorden();
    std::cout << "\n-- Postorden --" << std::endl;
    this->arbolDecision.mostrarPostorden();
}

void Hospital::menu() {
    int opcion = 0;
    while (opcion != 6) {
        std::cout << "\n=== HOSPITAL MARMAJA ===" << std::endl;
        std::cout << "1. Atender pacientes" << std::endl;
        std::cout << "2. Ver departamentos" << std::endl;
        std::cout << "3. Buscar paciente" << std::endl;
        std::cout << "4. Eliminar paciente" << std::endl;
        std::cout << "5. Ver arbol de decision" << std::endl;
        std::cout << "6. Salir" << std::endl;
        std::cout << "Seleccionar opcion: ";

        std::string linea;
        if (!std::getline(std::cin, linea)) return;   // se acabo la entrada

        if (!aEntero(linea, opcion)) {
            opcion = 0;
            std::cout << "Opcion invalida." << std::endl;
            continue;
        }

        if (opcion == 1) atenderPacientes();
        else if (opcion == 2) verDepartamentos();
        else if (opcion == 3) buscarPaciente();
        else if (opcion == 4) eliminarPaciente();
        else if (opcion == 5) verArbolDecision();
        else if (opcion == 6) std::cout << "Hasta luego." << std::endl;
        else std::cout << "Opcion invalida." << std::endl;
    }
}
