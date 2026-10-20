#include "Queue.h"
Queue::Queue(){
    this->front = nullptr;
}

void Queue::push(Paciente* p){
    Node* nuevoNodo = new Node(p);
    if(isEmpty()){
        front = nuevoNodo;
    } else {
        Node* actual = front;
        while(actual->getNext() != nullptr){
            actual = actual->getNext();
        }
        actual->setNext(nuevoNodo);
    }
}

bool Queue::isEmpty(){
    return front == nullptr;
}

Paciente* Queue::pop(){
    if(isEmpty()){
        return nullptr;
    }

    Node* actual = front;
    front = front->getNext();

    Paciente* p = actual->getPaciente();
    delete actual;

    return p;
}

Queue::~Queue() {
    while (front != nullptr) {
        Node* actual = front;
        front = front->getNext();
        
        delete actual->getPaciente();   
        
        delete actual;                  
    }
}
