#ifndef HASHMAP_H
#define HASHMAP_H

class Node;

class HashMap {
    public:
        HashMap();
        HashMap(const HashMap& orig);
        HashMap(HashMap&& orig) noexcept;
        HashMap& operator=(const HashMap& rhs);
        HashMap& operator=(HashMap&& rhs) noexcept;
        ~HashMap();
        int get_size() const;
        int get_capacity() const;
        double load_factor() const;
        bool empty() const;
        void clear();
        void insert(int key, int value);
        bool contains(int key) const;
        bool get(int key, int& out) const;
        void remove(int key);

    private:
        int size;
        int capacity; // Number of buckets
        Node** buckets;
        void insert_no_rehash(int key, int value);
        int hash(int key) const;
        void rehash();
};

#endif
