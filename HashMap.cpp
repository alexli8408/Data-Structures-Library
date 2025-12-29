#include "HashMap.h"

#include <cassert>

class Node {
    private:
        Node(int k, int v, Node* new_next): key{k}, value{v}, next{new_next} {

        }

        int key;
        int value;
        Node* next;

    friend class HashMap;
};

HashMap::HashMap(): size{0}, capacity{17}, buckets{new Node*[17]{}} {

}

HashMap::HashMap(const HashMap& orig): size{0}, capacity{orig.capacity}, buckets{new Node*[capacity]{}} {
    for (int k{0}; k < capacity; ++k) {
        for (Node* curr{orig.buckets[k]}; curr != nullptr; curr = curr->next) {
            insert_no_rehash(curr->key, curr->value);
        }
    }
}

HashMap::HashMap(HashMap&& orig) noexcept: size{orig.size}, capacity{orig.capacity}, buckets{orig.buckets} {
    orig.size = 0;
    orig.capacity = 17;
    orig.buckets = new Node*[17]{};
}

HashMap& HashMap::operator=(const HashMap& rhs) {
    if (this == &rhs) {
        return *this;
    }

    clear();
    delete[] buckets;
    size = 0;
    capacity = rhs.capacity;
    buckets = new Node*[capacity]{};

    for (int k{0}; k < capacity; ++k) {
        for (Node* curr{rhs.buckets[k]}; curr != nullptr; curr = curr->next) {
            insert_no_rehash(curr->key, curr->value);
        }
    }

    return *this;
}

HashMap& HashMap::operator=(HashMap&& rhs) noexcept {
    if (this == &rhs) {
        return *this;
    }

    clear();
    delete[] buckets;
    size = rhs.size;
    capacity = rhs.capacity;
    buckets = rhs.buckets;
    rhs.size = 0;
    rhs.capacity = 17;
    rhs.buckets = new Node*[17]{};

    return *this;
}

HashMap::~HashMap() {
    clear();
    delete[] buckets;
    buckets = nullptr;
}

int HashMap::get_size() const {
    return size;
}

int HashMap::get_capacity() const {
    return capacity;
}

double HashMap::load_factor() const {
    return 1.0 * size / capacity;
}

bool HashMap::empty() const {
    return size == 0;
}

void HashMap::clear() {
    for (int k{0}; k < capacity; ++k) {
        Node* curr{buckets[k]};

        while (curr != nullptr) {
            Node* temp{curr};
            curr = curr->next;
            delete temp;
        }

        buckets[k] = nullptr;
    }

    size = 0;
}

void HashMap::insert(int key, int value) {
    insert_no_rehash(key, value);

    if (size * 10 > capacity * 7) {
        rehash();
    }
}

// A key maps to a single index for the current capacity
bool HashMap::contains(int key) const {
    int i{hash(key)};
    assert(0 <= i && i < capacity);

    for (Node* curr{buckets[i]}; curr != nullptr; curr = curr->next) {
        if (curr->key == key) {
            return true;
        }
    }

    return false;
}

bool HashMap::get(int key, int& out) const {
    int i{hash(key)};
    assert(0 <= i && i < capacity);

    for (Node* curr{buckets[i]}; curr != nullptr; curr = curr->next) {
        if (curr->key == key) {
            out = curr->value;
            return true;
        }
    }

    return false;
}

void HashMap::remove(int key) {
    int i{hash(key)};
    assert(0 <= i && i < capacity);

    if (buckets[i] == nullptr) {
        return;
    }

    // At this point, the head of buckets[i] cannot be nullptr
    if (buckets[i]->key == key) {
        Node* temp{buckets[i]};
        buckets[i] = buckets[i]->next;
        delete temp;
        --size;
        return;
    }

    for (Node* curr{buckets[i]}; curr->next != nullptr; curr = curr->next) {
        if (curr->next->key == key) {
            Node* temp{curr->next};
            curr->next = curr->next->next;
            delete temp;
            --size;
            return;
        }
    }
}

void HashMap::insert_no_rehash(int key, int value) {
    int i{hash(key)};
    assert(0 <= i && i < capacity);

    for (Node* curr{buckets[i]}; curr != nullptr; curr = curr->next) {
        if (curr->key == key) {
            curr->value = value;
            return;
        }
    }

    buckets[i] = new Node{key, value, buckets[i]};
    ++size;
}

int HashMap::hash(int key) const {
    int index{key % capacity};

    if (index < 0) {
        index += capacity;
    }

    return index;
}

void HashMap::rehash() {
    size = 0;
    int old_capacity{capacity};
    capacity *= 2;
    Node** old_buckets{buckets};
    buckets = new Node*[capacity]{};

    for (int k{0}; k < old_capacity; ++k) {
        for (Node* curr{old_buckets[k]}; curr != nullptr; curr = curr->next) {
            insert_no_rehash(curr->key, curr->value);
        }
    }

    for (int k{0}; k < old_capacity; ++k) {
        Node* curr{old_buckets[k]};

        while (curr != nullptr) {
            Node* temp{curr};
            curr = curr->next;
            delete temp;
        }
    }

    delete[] old_buckets;
}

