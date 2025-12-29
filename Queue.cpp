#include "Queue.h"

void Queue::enqueue(double x) {
    data.push_back(x);
}

void Queue::dequeue() {
    data.pop_front();
}

double Queue::front() const {
    return data.front();
}

double Queue::back() const {
    return data.back();
}

bool Queue::empty() const {
    return data.empty();
}

std::size_t Queue::get_size() const {
    return data.get_size();
}

void Queue::clear() {
    data.clear();
}

void Queue::print() const {
    data.print();
}
