#ifndef NODE_H
#define NODE_H
#include "Paciente.h"

class Node{
    private:
        Node* next;
        Paciente* paciente;
    public:
        Node(Paciente* paciente);

        Node* getNext() const;
        Paciente* getPaciente() const;

        void setNext(Node* next);
        void setPaciente(Paciente* paciente);
};

#endif