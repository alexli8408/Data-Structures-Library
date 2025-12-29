#include "Stack.h"

#include <cassert>

void Stack::push(double value) {
    data.push_back(value);
}

void Stack::pop() {
    data.pop_back();
}

double Stack::top() const {
    assert(!empty());
    return data.back();
}

std::size_t Stack::get_size() const {
    return data.get_size();
}

bool Stack::empty() const {
    return data.empty();
}

void Stack::clear() {
    data.clear();
}

void Stack::print() const {
    data.print();
}
