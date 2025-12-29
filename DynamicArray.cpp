#include "DynamicArray.h"

#include <iostream>
#include <cassert>

DynamicArray::DynamicArray(): size{0}, capacity{1}, data{new double[capacity]{}} {

}

DynamicArray::DynamicArray(const std::size_t cap): size{0}, capacity{cap == 0 ? 1 : cap}, data{new double[capacity]{}} {

}

DynamicArray::DynamicArray(const DynamicArray& orig): size{orig.size}, capacity{orig.capacity}, data{new double[capacity]{}} {
    for (std::size_t k{0}; k < size; ++k) {
        data[k] = orig.data[k];
    }
}

DynamicArray::DynamicArray(DynamicArray&& orig) noexcept: size{orig.size}, capacity{orig.capacity}, data{orig.data} {
    orig.size = 0;
    orig.capacity = 0;
    orig.data = nullptr;
}

DynamicArray& DynamicArray::operator=(const DynamicArray& rhs) {
    if (this == &rhs) {
        return *this;
    }

    delete[] data;
    size = rhs.size;
    capacity = rhs.capacity;
    data = new double[capacity]{};

    for (std::size_t k{0}; k < size; ++k) {
        data[k] = rhs.data[k];
    }

    return *this;
}

DynamicArray& DynamicArray::operator=(DynamicArray&& rhs) noexcept {
    if (this == &rhs) {
        return *this;
    }

    delete[] data;
    size = rhs.size;
    capacity = rhs.capacity;
    data = rhs.data;
    rhs.size = 0;
    rhs.capacity = 0;
    rhs.data = nullptr;

    return *this;
}

DynamicArray::~DynamicArray() {
    delete[] data;
    size = 0;
    capacity = 0;
    data = nullptr;
}

double& DynamicArray::operator[](const std::size_t index) {
    assert(index < size);

    return data[index];
}

const double& DynamicArray::operator[](const std::size_t index) const {
    assert(index < size);

    return data[index];
}

double& DynamicArray::front() {
    assert(size > 0);

    return data[0];
}

const double& DynamicArray::front() const {
    assert(size > 0);

    return data[0];
}

double& DynamicArray::back() {
    assert(size > 0);

    return data[size - 1];
}

const double& DynamicArray::back() const {
    assert(size > 0);

    return data[size - 1];
}

void DynamicArray::push_back(const double value) {
    if (capacity == 0) {
        reserve(1);
    } else if (size == capacity) {
        reserve(capacity * 2);
    }

    data[size] = value;
    ++size;
}

void DynamicArray::pop_back() {
    if (size == 0) {
        return;
    }

    --size;
}

std::size_t DynamicArray::get_size() const {
    return size;
}

std::size_t DynamicArray::get_capacity() const {
    return capacity;
}

bool DynamicArray::empty() const {
    return size == 0;
}

void DynamicArray::reserve(const std::size_t new_capacity) {
    if (new_capacity <= capacity) {
        return;
    }

    double* temp{data};
    data = new double[new_capacity]{};

    for (std::size_t k{0}; k < size; ++k) {
        data[k] = temp[k];
    }

    delete[] temp;
    capacity = new_capacity;
}

void DynamicArray::resize(const std::size_t new_size, const double default_value) {
    if (new_size <= size) {
        size = new_size;
        return;
    }

    if (new_size > capacity) {
        reserve(new_size);
    }

    for (std::size_t k{size}; k < new_size; ++k) {
        data[k] = default_value;
    }

    size = new_size;
}

void DynamicArray::insert(const std::size_t index, const double value) {
    if (index > size) {
        return;
    }

    if (capacity == 0) {
        reserve(1);
    } else if (size == capacity) {
        reserve(capacity * 2);
    }

    for (std::size_t k{size}; k > index; --k) {
        data[k] = data[k - 1];
    }

    data[index] = value;
    ++size;
}

void DynamicArray::erase(const std::size_t index) {
    if (index >= size) {
        return;
    }

    for (std::size_t k{index}; k < size - 1; ++k) {
        data[k] = data[k + 1];
    }

    --size;
}

void DynamicArray::clear() {
    size = 0;
}

void DynamicArray::print() const {
    if (size == 0) {
        std::cout << "[]\n";

        return;
    }

    std::cout << "[" << data[0];

    for (std::size_t k{1}; k < size; ++k) {
        std::cout << ", " << data[k];
    }

    std::cout << "]\n";
}

