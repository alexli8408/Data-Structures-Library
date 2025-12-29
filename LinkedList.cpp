#include "LinkedList.h"

#include <iostream>
#include <cassert>

class Node {
    private:
        Node(double new_value, Node* new_next): data{new_value}, next{new_next} {

        }

        double data;
        Node* next;

    friend class LinkedList;
};

LinkedList::LinkedList(): head{nullptr}, tail{nullptr}, size{0} {

}

LinkedList::LinkedList(const LinkedList& orig): head{nullptr}, tail{nullptr}, size{0} {
    for (Node* curr{orig.head}; curr != nullptr; curr = curr->next) {
        push_back(curr->data);
    }
}

LinkedList::LinkedList(LinkedList&& orig) noexcept: head{orig.head}, tail{orig.tail}, size{orig.size} {
    orig.head = nullptr;
    orig.tail = nullptr;
    orig.size = 0;
}

LinkedList& LinkedList::operator=(const LinkedList& rhs) {
    if (this == &rhs) {
        return *this;
    }

    clear();

    for (Node* curr{rhs.head}; curr != nullptr; curr = curr->next) {
        push_back(curr->data);
    }

    return *this;
}

LinkedList& LinkedList::operator=(LinkedList&& rhs) noexcept {
    if (this == &rhs) {
        return *this;
    }

    clear();
    head = rhs.head;
    tail = rhs.tail;
    size = rhs.size;
    rhs.head = nullptr;
    rhs.tail = nullptr;
    rhs.size = 0;

    return *this;
}

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::push_front(double value) {
    if (empty()) {
        head = new Node{value, nullptr};
        tail = head;
        ++size;
        return;
    }

    head = new Node{value, head};
    ++size;
}

void LinkedList::push_back(double value) {
    if (empty()) {
        head = new Node{value, nullptr};
        tail = head;
        ++size;
        return;
    }

    tail->next = new Node{value, nullptr};
    tail = tail->next;
    ++size;
}

void LinkedList::pop_front() {
    if (empty()) {
        return;
    }

    Node* temp{head};
    head = head->next;
    delete temp;
    --size;

    if (head == nullptr) {
        tail = nullptr;
    }
}

void LinkedList::pop_back() {
    if (empty()) {
        return;
    }

    if (head->next == nullptr) {
        pop_front();
        return;
    }

    Node* curr{head};

    while (curr->next != tail) {
        curr = curr->next;
    }

    delete tail;
    tail = curr;
    tail->next = nullptr;
    --size;
}

std::size_t LinkedList::get_size() const {
    return size;
}

bool LinkedList::empty() const {
    return head == nullptr && size == 0;
}

void LinkedList::insert(std::size_t index, double value) {
    assert(index <= size);

    if (index == 0) {
        push_front(value);
        return;
    }

    if (index == size) {
        push_back(value);
        return;
    }

    Node* curr{head};

    for (std::size_t count{1}; count < index; ++count) {
        curr = curr->next;
    }

    curr->next = new Node{value, curr->next};
    ++size;
}

void LinkedList::erase(std::size_t index) {
    assert(index < size);

    if (index == 0) {
        pop_front();
        return;
    }

    if (index == size - 1) {
        pop_back();
        return;
    }

    Node* curr{head};

    for (std::size_t count{1}; count < index; ++count) {
        curr = curr->next;
    }

    Node* temp{curr->next};
    curr->next = curr->next->next;
    delete temp;
    --size;
}

double LinkedList::front() const {
    assert(!empty());

    return head->data;
}

double LinkedList::back() const {
    assert(!empty());
    
    return tail->data;
}

int LinkedList::find(double value) const {
    int count{0};

    for (const Node* curr{head}; curr != nullptr; curr = curr->next) {
        if (curr->data == value) {
            return count;
        }

        ++count;
    }

    return -1;
}

bool LinkedList::contains(double value) const {
    return find(value) >= 0;
}

void LinkedList::clear() {
    while (head != nullptr) {
        pop_front();
    }
}

void LinkedList::print() const {
    std::cout << "(Size = " << size << ") Head -> ";

    for (const Node* curr{head}; curr != nullptr; curr = curr->next) {
        std::cout << curr->data << " -> ";
    }

    std::cout << "Null\n";
}
