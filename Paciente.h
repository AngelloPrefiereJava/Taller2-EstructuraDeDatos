#ifndef PACIENTE_H
#define PACIENTE_H
#include <string>

class Paciente{
    private:
        std::string id,nombre;
        int edad;
        float temperatura, presionArterial;
        int dolor;
        std::string tipoDolor;
        int trauma,sintomasNeurologicos,requiereCirugia,diasHospitalizacion;

    public:
        Paciente(std::string id, std::string nombre, int edad, float temperatura, float presionArterial,
        int dolor, std::string tipoDolor, int trauma, int sintomasNeurologicos, int requiereCirugia,
        int diasHospitalizacion);

        std::string getId() const;
        std::string getNombre()const;
        int getEdad() const;
        float getTemperatura() const;
        float getPresionArterial() const;
        int getDolor()const;
        std::string getTipoDolor()const;
        int getTrauma()const;
        int getSintomasNeurologicos()const;
        int getRequiereCirugia()const;
        int getDiasHospitalizacion()const;
};

#endif