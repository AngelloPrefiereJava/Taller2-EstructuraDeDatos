#ifndef QUEUE_H
#define QUEUE_H
#include "Node.h"

class Queue{
    private:
        Node* front;
    public:
        Queue();

        void push(Paciente* p);
        Paciente* pop();
        bool isEmpty();
        ~Queue();
};

#endif