#include "Node.h"

Node::Node(Paciente* paciente){
    this->paciente = paciente;
    this->next = nullptr;
}

Node* Node::getNext() const{
    return this->next;
}

Paciente* Node::getPaciente() const{
    return this->paciente;
}

void Node::setNext(Node* next){
    this->next = next;
}

void Node::setPaciente(Paciente* paciente){
    this->paciente = paciente;
}