#include <iostream>
#include <string>
#include "Hospital.h"

int main(int argc, char* argv[]) {
    std::string archivo = "pacientes.txt";
    if (argc > 1) archivo = argv[1];

    Hospital hospital;
    if (hospital.cargarDesdeArchivo(archivo) < 0) return 1;

    hospital.menu();
    return 0;
}