#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <cstddef>

class DynamicArray {
    public:
        DynamicArray();
        explicit DynamicArray(const std::size_t cap);
        DynamicArray(const DynamicArray& orig);
        DynamicArray(DynamicArray&& orig) noexcept;
        DynamicArray& operator=(const DynamicArray& rhs);
        DynamicArray& operator=(DynamicArray&& rhs) noexcept;
        ~DynamicArray();
        double& operator[](const std::size_t index);
        const double& operator[](const std::size_t index) const;
        double& front();
        const double& front() const;
        double& back();
        const double& back() const;
        void push_back(const double value);
        void pop_back();
        std::size_t get_size() const;
        std::size_t get_capacity() const;
        bool empty() const;
        void reserve(const std::size_t new_capacity);
        void resize(const std::size_t new_size, const double default_value = 0.0);
        void insert(const std::size_t index, const double value);
        void erase(const std::size_t index);
        void clear();
        void print() const;

    private:
        std::size_t size;
        std::size_t capacity;
        double* data;

};

#endif
