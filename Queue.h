#ifndef QUEUE_H
#define QUEUE_H

#include "LinkedList.h"

#include <cstddef>

class Queue {
    public:
        void enqueue(double x);
        void dequeue();
        double front() const;
        double back() const;
        bool empty() const;
        std::size_t get_size() const;
        void clear();
        void print() const;

    private:
        LinkedList data;
};

#endif
