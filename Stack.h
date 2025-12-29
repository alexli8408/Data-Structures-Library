#ifndef STACK_H
#define STACK_H

#include "DynamicArray.h"

#include <cstddef>

class Stack {
    public:
        void push(double value);
        void pop();
        double top() const;
        std::size_t get_size() const;
        bool empty() const;
        void clear();
        void print() const;

    private:
        DynamicArray data;
};

#endif
