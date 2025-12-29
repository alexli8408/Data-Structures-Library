#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <cstddef>

class Node;

class LinkedList {
    public:
        LinkedList();
        LinkedList(const LinkedList& orig);
        LinkedList(LinkedList&& orig) noexcept;
        LinkedList& operator=(const LinkedList& rhs);
        LinkedList& operator=(LinkedList&& rhs) noexcept;
        ~LinkedList();
        void push_front(double value);
        void push_back(double value);
        void pop_front();
        void pop_back();
        std::size_t get_size() const;
        bool empty() const;
        void insert(std::size_t index, double value);
        void erase(std::size_t index);
        double front() const;
        double back() const;
        int find(double value) const;
        bool contains(double value) const;
        void clear();
        void print() const;

    private:
        Node* head;
        Node* tail;
        std::size_t size;
};

#endif
