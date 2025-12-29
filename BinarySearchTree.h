#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <cstddef>

class Node;

class BinarySearchTree {
    public:
        BinarySearchTree();
        BinarySearchTree(const BinarySearchTree& orig);
        BinarySearchTree(BinarySearchTree&& orig) noexcept;
        BinarySearchTree& operator=(const BinarySearchTree& rhs);
        BinarySearchTree& operator=(BinarySearchTree&& rhs) noexcept;
        ~BinarySearchTree();
        void clear();
        std::size_t get_size() const;
        bool empty() const;
        void insert(double value);
        bool contains(double value) const;
        double min() const;
        double max() const;
        std::size_t height() const;
        void inorder_print() const;
        void preorder_print() const;
        void postorder_print() const;
        void levelorder_print() const;
        void erase(double value);
        bool is_valid_bst() const;

    private:
        Node* root;
        std::size_t size;
        Node* clone(const Node* curr) const;
        void clear(Node*& curr);
        std::size_t height(const Node* curr) const;
        void inorder_print(const Node* curr) const;
        void preorder_print(const Node* curr) const;
        void postorder_print(const Node* curr) const;
        void levelorder_print(const Node* curr) const;
        void erase(Node*& curr, double value);
        bool is_valid_bst(const Node* curr, const Node* min_node, const Node* max_node) const;
};

#endif
