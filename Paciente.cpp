#include "Paciente.h"

Paciente::Paciente(std::string id, std::string nombre, int edad, float temperatura, float presionArterial,
        int dolor, std::string tipoDolor, int trauma, int sintomasNeurologicos, int requiereCirugia,
        int diasHospitalizacion){

        this->id = id;
        this->nombre = nombre;
        this->edad = edad;
        this->temperatura = temperatura;
        this->presionArterial = presionArterial;
        this->dolor = dolor;
        this->tipoDolor = tipoDolor;
        this->trauma = trauma;
        this->sintomasNeurologicos = sintomasNeurologicos;
        this->requiereCirugia = requiereCirugia;
        this->diasHospitalizacion = diasHospitalizacion;
    }

        std::string Paciente::getId() const{
            return this->id;
        }
        std::string Paciente::getNombre()const{
            return this->nombre;
        }
        int Paciente::getEdad()const{
            return this->edad;
        }
        float Paciente::getTemperatura()const{
            return this->temperatura;
        }
        float Paciente::getPresionArterial()const{
            return this->presionArterial;
        }
        int Paciente::getDolor()const{
            return this->dolor;
        }
        std::string Paciente::getTipoDolor()const{
            return this->tipoDolor;
        }
        int Paciente::getTrauma()const{
            return this->trauma;
        }
        int Paciente::getSintomasNeurologicos()const{
            return this->sintomasNeurologicos;
        }
        int Paciente::getRequiereCirugia()const{
            return this->requiereCirugia;
        }
        int Paciente::getDiasHospitalizacion()const{
            return this->diasHospitalizacion;
        }