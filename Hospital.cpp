#include "Hospital.h"

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