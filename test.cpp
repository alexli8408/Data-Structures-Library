// Unit tests for data structures library
// Compile: clang++ -std=c++17 -O2 -Wall -Wextra -Wpedantic test.cpp DynamicArray.cpp \
// Stack.cpp LinkedList.cpp Queue.cpp HashMap.cpp BinarySearchTree.cpp -o test && ./test

#include "DynamicArray.h"
#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include "HashMap.h"
#include "BinarySearchTree.h"

#include <iostream>
#include <cassert>
#include <cstddef>

// Unit test helpers
static int g_tests_run{0};

#define RUN_TEST(fn)                                                      \
    do {                                                                  \
        ++g_tests_run;                                                    \
        fn();                                                             \
        std::cout << "[PASS] " #fn "\n";                                  \
    } while (0)

static void assert_double_eq(double a, double b, double eps = 1e-12) {
    double diff{(a > b) ? (a - b) : (b - a)};
    assert(diff <= eps);
}

// DynamicArray tests
static void test_dynamicarray_basic_push_pop_index() {
    DynamicArray a;
    assert(a.get_size() == 0);
    assert(a.empty());
    a.push_back(1.0);
    a.push_back(2.0);
    a.push_back(3.0);
    assert(a.get_size() == 3);
    assert(!a.empty());
    assert_double_eq(a.front(), 1.0);
    assert_double_eq(a.back(), 3.0);
    assert_double_eq(a[0], 1.0);
    assert_double_eq(a[1], 2.0);
    assert_double_eq(a[2], 3.0);
    a.pop_back();
    assert(a.get_size() == 2);
    assert_double_eq(a.back(), 2.0);
    a.clear();
    assert(a.get_size() == 0);
    assert(a.empty());
}

static void test_dynamicarray_reserve_resize_insert_erase() {
    DynamicArray a(1);
    assert(a.get_capacity() >= 1);
    a.reserve(10);
    assert(a.get_capacity() >= 10);
    assert(a.get_size() == 0);
    a.resize(5, 7.5);
    assert(a.get_size() == 5);

    for (std::size_t i{0}; i < a.get_size(); ++i) {
        assert_double_eq(a[i], 7.5);
    }

    a.insert(0, 1.0);
    a.insert(3, 2.0);
    a.insert(a.get_size(), 3.0);
    assert_double_eq(a[0], 1.0);
    assert_double_eq(a.back(), 3.0);
    std::size_t old_size{a.get_size()};
    a.erase(0);
    assert(a.get_size() == old_size - 1);
    old_size = a.get_size();
    a.erase(2);
    assert(a.get_size() == old_size - 1);
    a.resize(2);
    assert(a.get_size() == 2);
}

static void test_dynamicarray_copy_and_move() {
    DynamicArray a;

    for (int i{0}; i < 20; ++i) {
        a.push_back(1.0 * i);
    }

    DynamicArray b(a);
    assert(b.get_size() == a.get_size());

    for (std::size_t i{0}; i < a.get_size(); ++i) {
        assert_double_eq(a[i], b[i]);
    }

    DynamicArray c;
    c = b;
    assert(c.get_size() == b.get_size());

    for (std::size_t i{0}; i < b.get_size(); ++i) {
        assert_double_eq(b[i], c[i]);
    }

    DynamicArray d(std::move(a));
    assert(d.get_size() == 20);
    assert_double_eq(d[0], 0.0);
    assert_double_eq(d[19], 19.0);
    DynamicArray e;
    e = std::move(b);
    assert(e.get_size() == 20);
    assert_double_eq(e[5], 5.0);
}

// LinkedList tests
static void test_linkedlist_push_pop_front_back() {
    LinkedList l;
    assert(l.empty());
    assert(l.get_size() == 0);
    l.push_front(2.0);
    assert_double_eq(l.front(), 2.0);
    assert_double_eq(l.back(), 2.0);
    l.push_front(1.0);
    l.push_back(3.0);
    assert(l.get_size() == 3);
    assert_double_eq(l.front(), 1.0);
    assert_double_eq(l.back(), 3.0);
    l.pop_front();
    assert(l.get_size() == 2);
    assert_double_eq(l.front(), 2.0);
    l.pop_back();
    assert(l.get_size() == 1);
    assert_double_eq(l.back(), 2.0);
    l.pop_back();
    assert(l.empty());
    assert(l.get_size() == 0);
}

static void test_linkedlist_insert_erase_find_contains() {
    LinkedList l;
    l.push_back(1.0);
    l.push_back(3.0);
    l.push_back(5.0);
    l.insert(1, 2.0);
    l.insert(3, 4.0);
    assert(l.get_size() == 5);
    assert_double_eq(l.front(), 1.0);
    assert_double_eq(l.back(), 5.0);
    assert(l.find(1.0) == 0);
    assert(l.find(3.0) == 2);
    assert(l.find(5.0) == 4);
    assert(l.find(999.0) == -1);
    assert(l.contains(4.0));
    assert(!l.contains(-1.0));
    l.erase(0);
    l.erase(2);
    assert(l.get_size() == 3);
    assert(l.find(4.0) == -1);
    l.clear();
    assert(l.empty());
}

static void test_linkedlist_copy_and_move() {
    LinkedList a;

    for (int i{0}; i < 10; ++i) {
        a.push_back(1.0 * i);
    }

    LinkedList b(a);
    assert(b.get_size() == a.get_size());
    assert_double_eq(b.front(), 0.0);
    assert_double_eq(b.back(), 9.0);
    LinkedList c;
    c = b;
    assert(c.get_size() == 10);
    assert_double_eq(c.back(), 9.0);
    LinkedList d(std::move(a));
    assert(d.get_size() == 10);
    assert_double_eq(d.front(), 0.0);
    LinkedList e;
    e = std::move(b);
    assert(e.get_size() == 10);
    assert_double_eq(e.front(), 0.0);
}

// Stack tests
static void test_stack_basic_lifo() {
    Stack s;
    assert(s.empty());
    assert(s.get_size() == 0);
    s.push(10.0);
    s.push(20.0);
    s.push(30.0);
    assert(!s.empty());
    assert(s.get_size() == 3);
    assert_double_eq(s.top(), 30.0);
    s.pop();
    assert(s.get_size() == 2);
    assert_double_eq(s.top(), 20.0);
    s.clear();
    assert(s.empty());
    assert(s.get_size() == 0);
}

static void test_stack_many_ops() {
    Stack s;

    for (int i{0}; i < 100; ++i) {
        s.push(1.0 * i);
    }

    assert(s.get_size() == 100);
    assert_double_eq(s.top(), 99.0);

    for (int i{0}; i < 50; ++i) {
        s.pop();
    }

    assert(s.get_size() == 50);
    assert_double_eq(s.top(), 49.0);
}

// Queue tests
static void test_queue_basic_fifo() {
    Queue q;
    assert(q.empty());
    assert(q.get_size() == 0);
    q.enqueue(1.0);
    q.enqueue(2.0);
    q.enqueue(3.0);
    assert(!q.empty());
    assert(q.get_size() == 3);
    assert_double_eq(q.front(), 1.0);
    assert_double_eq(q.back(), 3.0);
    q.dequeue();
    assert(q.get_size() == 2);
    assert_double_eq(q.front(), 2.0);
    q.dequeue();
    q.dequeue();
    assert(q.empty());
    assert(q.get_size() == 0);
}

static void test_queue_many_ops() {
    Queue q;
    for (int i{0}; i < 50; ++i) {
        q.enqueue(1.0 * i);
    }

    assert(q.get_size() == 50);
    assert_double_eq(q.front(), 0.0);
    assert_double_eq(q.back(), 49.0);

    for (int i{0}; i < 25; ++i) {
        q.dequeue();
    }

    assert(q.get_size() == 25);
    assert_double_eq(q.front(), 25.0);
    q.clear();
    assert(q.empty());
}

// HashMap tests
static void test_hashmap_basic_insert_get_remove() {
    HashMap m;
    assert(m.get_size() == 0);
    assert(m.empty());
    m.insert(10, 100);
    m.insert(20, 200);
    m.insert(-5, 50);
    assert(m.get_size() == 3);
    assert(m.contains(10));
    assert(m.contains(20));
    assert(m.contains(-5));
    assert(!m.contains(999));
    int out{0};
    assert(m.get(10, out) && out == 100);
    assert(m.get(20, out) && out == 200);
    assert(m.get(-5, out) && out == 50);
    assert(!m.get(123, out));
    m.insert(10, 111);
    assert(m.get(10, out) && out == 111);
    assert(m.get_size() == 3);
    m.remove(20);
    assert(!m.contains(20));
    assert(m.get_size() == 2);
    m.clear();
    assert(m.empty());
    assert(m.get_size() == 0);
}

static void test_hashmap_rehash_stability() {
    HashMap m;

    for (int k{0}; k < 50; ++k) {
        m.insert(k, k * 10);
    }

    assert(m.get_size() == 50);
    int out{0};

    for (int k{0}; k < 50; ++k) {
        assert(m.get(k, out));
        assert(out == k * 10);
    }

    for (int k{0}; k < 25; ++k) {
        m.remove(k);
    }

    assert(m.get_size() == 25);

    for (int k{0}; k < 25; ++k) {
        assert(!m.contains(k));
    }

    for (int k{25}; k < 50; ++k) {
        assert(m.get(k, out) && out == k * 10);
    }
}

static void test_hashmap_copy_and_move() {
    HashMap a;

    for (int k{0}; k < 30; ++k) {
        a.insert(k, 1000 + k);
    }

    HashMap b(a);
    assert(b.get_size() == a.get_size());
    int out{0};

    for (int k{0}; k < 30; ++k) {
        assert(b.get(k, out) && out == 1000 + k);
    }

    HashMap c;
    c = b;
    assert(c.get_size() == 30);
    assert(c.get(10, out) && out == 1010);
    HashMap d(std::move(a));
    assert(d.get_size() == 30);
    assert(d.get(0, out) && out == 1000);
    HashMap e;
    e = std::move(b);
    assert(e.get_size() == 30);
    assert(e.get(29, out) && out == 1029);
}

// BinarySearchTree tests
static void test_bst_insert_contains_min_max_height_valid() {
    BinarySearchTree t;
    assert(t.empty());
    assert(t.get_size() == 0);
    assert(t.is_valid_bst());
    t.insert(5);
    t.insert(3);
    t.insert(7);
    t.insert(2);
    t.insert(4);
    t.insert(6);
    t.insert(8);
    assert(!t.empty());
    assert(t.get_size() == 7);
    assert(t.contains(5));
    assert(t.contains(2));
    assert(t.contains(8));
    assert(!t.contains(999));
    assert_double_eq(t.min(), 2.0);
    assert_double_eq(t.max(), 8.0);
    assert(t.height() == 3);
    assert(t.is_valid_bst());
}

static void test_bst_no_duplicates() {
    BinarySearchTree t;
    t.insert(5);
    t.insert(5);
    t.insert(5);
    assert(t.get_size() == 1);
    assert(t.contains(5));
    assert(t.is_valid_bst());
}

static void test_bst_erase_cases() {
    BinarySearchTree t;

    for (double v : {5,3,7,2,4,6,8}) {
        t.insert(v);
    }

    assert(t.get_size() == 7);
    t.erase(2);
    assert(!t.contains(2));
    assert(t.get_size() == 6);
    assert(t.is_valid_bst());
    t.erase(8);
    assert(!t.contains(8));
    assert(t.get_size() == 5);
    assert(t.is_valid_bst());
    t.erase(7);
    assert(!t.contains(7));
    assert(t.get_size() == 4);
    assert(t.is_valid_bst());
    t.erase(5);
    assert(!t.contains(5));
    assert(t.get_size() == 3);
    assert(t.is_valid_bst());
    t.clear();
    assert(t.empty());
    assert(t.get_size() == 0);
}

static void test_bst_copy_and_move() {
    BinarySearchTree a;

    for (double v : {10,5,15,3,7,12,18}) {
        a.insert(v);
    }

    BinarySearchTree b(a);
    assert(b.get_size() == a.get_size());
    assert(b.contains(7));
    assert_double_eq(b.min(), 3.0);
    assert_double_eq(b.max(), 18.0);
    assert(b.is_valid_bst());
    BinarySearchTree c;
    c = b;
    assert(c.get_size() == 7);
    assert(c.contains(12));
    assert(c.is_valid_bst());
    BinarySearchTree d(std::move(a));
    assert(d.get_size() == 7);
    assert(d.contains(15));
    BinarySearchTree e;
    e = std::move(b);
    assert(e.get_size() == 7);
    assert(e.contains(5));
}

// Main
int main() {
    // DynamicArray
    RUN_TEST(test_dynamicarray_basic_push_pop_index);
    RUN_TEST(test_dynamicarray_reserve_resize_insert_erase);
    RUN_TEST(test_dynamicarray_copy_and_move);

    // LinkedList
    RUN_TEST(test_linkedlist_push_pop_front_back);
    RUN_TEST(test_linkedlist_insert_erase_find_contains);
    RUN_TEST(test_linkedlist_copy_and_move);

    // Stack
    RUN_TEST(test_stack_basic_lifo);
    RUN_TEST(test_stack_many_ops);

    // Queue
    RUN_TEST(test_queue_basic_fifo);
    RUN_TEST(test_queue_many_ops);

    // HashMap
    RUN_TEST(test_hashmap_basic_insert_get_remove);
    RUN_TEST(test_hashmap_rehash_stability);
    RUN_TEST(test_hashmap_copy_and_move);

    // BinarySearchTree
    RUN_TEST(test_bst_insert_contains_min_max_height_valid);
    RUN_TEST(test_bst_no_duplicates);
    RUN_TEST(test_bst_erase_cases);
    RUN_TEST(test_bst_copy_and_move);
    std::cout << "\nAll tests passed (" << g_tests_run << " tests).\n";

    return 0;
}
