#include "BinarySearchTree.h"

#include <iostream>
#include <cassert>

class PtrNode {
    private:
        PtrNode(const Node* value, PtrNode* new_next): data{value}, next{new_next} {

        }

        const Node* data;
        PtrNode* next;

    friend class PtrQueue;
};

class PtrQueue {
    public:
        PtrQueue(): head{nullptr}, tail{nullptr} {

        }

        PtrQueue(const PtrQueue& orig) = delete;
        PtrQueue(PtrQueue&& orig) noexcept = delete;
        PtrQueue& operator=(const PtrQueue& rhs) = delete;
        PtrQueue& operator=(PtrQueue&& rhs) noexcept = delete;

        ~PtrQueue() {
            while (!empty()) {
                dequeue();
            }
        }

        bool empty() const {
            return head == nullptr;
        }

        void enqueue(const Node* x) {
            if (empty()) {
                head = new PtrNode{x, nullptr};
                tail = head;
                return;
            }

            tail->next = new PtrNode{x, nullptr};
            tail = tail->next;
        }

        void dequeue() {
            if (empty()) {
                return;
            }

            PtrNode* temp{head};
            head = head->next;
            delete temp;

            if (head == nullptr) {
                tail = nullptr;
            }
        }

        const Node* front() const {
            assert(!empty());
            return head->data;
        }

    private:
        PtrNode* head;
        PtrNode* tail;
};

class Node {
    private:
        Node(double value): data{value}, left{nullptr}, right{nullptr} {

        }

        double data;
        Node* left;
        Node* right;

    friend class BinarySearchTree;
};

BinarySearchTree::BinarySearchTree(): root{nullptr}, size{0} {

}

BinarySearchTree::BinarySearchTree(const BinarySearchTree& orig): root{clone(orig.root)}, size{orig.size} {

}

BinarySearchTree::BinarySearchTree(BinarySearchTree&& orig) noexcept: root{orig.root}, size{orig.size} {
    orig.root = nullptr;
    orig.size = 0;
}

BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& rhs) {
    if (this == &rhs) {
        return *this;
    }

    clear();
    root = clone(rhs.root);
    size = rhs.size;

    return *this;
}

BinarySearchTree& BinarySearchTree::operator=(BinarySearchTree&& rhs) noexcept {
    if (this == &rhs) {
        return *this;
    }

    clear();
    root = rhs.root;
    size = rhs.size;
    rhs.root = nullptr;
    rhs.size = 0;

    return *this;
}

BinarySearchTree::~BinarySearchTree() {
    clear();
}

void BinarySearchTree::clear() {
    clear(root);
    size = 0;
}

std::size_t BinarySearchTree::get_size() const {
    return size;
}

bool BinarySearchTree::empty() const {
    return size == 0;
}

void BinarySearchTree::insert(double value) {
    if (root == nullptr) {
        root = new Node{value};
        ++size;
        return;
    }

    Node* curr{root};

    while (true) {
        if (value == curr->data) {
            return;
        } else if (value < curr->data) {
            if (curr->left == nullptr) {
                curr->left = new Node{value};
                ++size;
                return;
            } else {
                curr = curr->left;
            }
        } else {
            if (curr->right == nullptr) {
                curr->right = new Node{value};
                ++size;
                return;
            } else {
                curr = curr->right;
            }
        }
    }
}

bool BinarySearchTree::contains(double value) const {
    if (root == nullptr) {
        return false;
    }

    const Node* curr{root};

    while (true) {
        if (value == curr->data) {
            return true;
        } else if (value < curr->data) {
            if (curr->left == nullptr) {
                return false;
            } else {
                curr = curr->left;
            }
        } else {
            if (curr->right == nullptr) {
                return false;
            } else {
                curr = curr->right;
            }
        }
    }
}

double BinarySearchTree::min() const {
    assert(!empty());
    const Node* curr{root};

    while (curr->left != nullptr) {
        curr = curr->left;
    }

    return curr->data;
}

double BinarySearchTree::max() const {
    assert(!empty());
    const Node* curr{root};

    while (curr->right != nullptr) {
        curr = curr->right;
    }

    return curr->data;
}

std::size_t BinarySearchTree::height() const {
    return height(root);
}

void BinarySearchTree::inorder_print() const {
    inorder_print(root);
    std::cout << "\n";
}

void BinarySearchTree::preorder_print() const {
    preorder_print(root);
    std::cout << "\n";
}

void BinarySearchTree::postorder_print() const {
    postorder_print(root);
    std::cout << "\n";
}

void BinarySearchTree::levelorder_print() const {
    levelorder_print(root);
    std::cout << "\n";
}

void BinarySearchTree::erase(double value) {
    erase(root, value);
}

bool BinarySearchTree::is_valid_bst() const {
    return is_valid_bst(root, nullptr, nullptr);
}

Node* BinarySearchTree::clone(const Node* curr) const {
    if (curr == nullptr) {
        return nullptr;
    }

    Node* new_node{new Node{curr->data}};
    new_node->left  = clone(curr->left);
    new_node->right = clone(curr->right);

    return new_node;
}

void BinarySearchTree::clear(Node*& curr) {
    if (curr == nullptr) {
        return;
    }

    clear(curr->left);
    clear(curr->right);
    delete curr;
    curr = nullptr;
}

std::size_t BinarySearchTree::height(const Node* curr) const {
    if (curr == nullptr) {
        return 0;
    }

    std::size_t l{height(curr->left)};
    std::size_t r{height(curr->right)};

    return 1 + (l >= r ? l : r);
}

void BinarySearchTree::inorder_print(const Node* curr) const {
    if (curr == nullptr) {
        return;
    }

    inorder_print(curr->left);
    std::cout << curr->data << " ";
    inorder_print(curr->right);
}

void BinarySearchTree::preorder_print(const Node* curr) const {
    if (curr == nullptr) {
        return;
    }

    std::cout << curr->data << " ";
    preorder_print(curr->left);
    preorder_print(curr->right);
}

void BinarySearchTree::postorder_print(const Node* curr) const {
    if (curr == nullptr) {
        return;
    }

    postorder_print(curr->left);
    postorder_print(curr->right);
    std::cout << curr->data << " ";
}

void BinarySearchTree::levelorder_print(const Node* curr) const {
    if (curr == nullptr) {
        return;
    }

    PtrQueue q;
    q.enqueue(curr);

    while (!q.empty()) {
        const Node* temp{q.front()};
        q.dequeue();
        std::cout << temp->data << " ";

        if (temp->left != nullptr) {
            q.enqueue(temp->left);
        }

        if(temp->right != nullptr) {
            q.enqueue(temp->right);
        }
    }
}

void BinarySearchTree::erase(Node*& curr, double value) {
    if (curr == nullptr) {
        return;
    } else if (value == curr->data) {
        if (curr->left == nullptr && curr->right == nullptr) {
            delete curr;
            curr = nullptr;
            --size;
        } else if (curr->left == nullptr) {
            Node* temp{curr};
            curr = curr->right;
            delete temp;
            --size;
        } else if (curr->right == nullptr) {
            Node* temp{curr};
            curr = curr->left;
            delete temp;
            --size;
        } else {
            Node* prev{curr};
            Node* temp{curr->right};

            while (temp->left != nullptr) {
                prev = temp;
                temp = temp->left;
            }

            curr->data = temp->data;

            if (prev->left == temp) {
                prev->left = temp->right;
            } else {
                prev->right = temp->right;
            }

            delete temp;
            --size;
        }
    } else if (value < curr->data) {
        erase(curr->left, value);
    } else {
        erase(curr->right, value);
    }
}

bool BinarySearchTree::is_valid_bst(const Node* curr, const Node* min_node, const Node* max_node) const {
    if (curr == nullptr) {
        return true;
    }

    if (min_node != nullptr && curr->data <= min_node->data) {
        return false;
    }

    if (max_node != nullptr && curr->data >= max_node->data) {
        return false;
    }

    return is_valid_bst(curr->left, min_node, curr) && is_valid_bst(curr->right, curr, max_node);
}

