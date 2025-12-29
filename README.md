# Data Structures Library (C++)

A C++ data structures library implemented from scratch for learning, unit testing, and
performance testing against the C++ standard library.

The goal of this project is to learn core data structures, memory management, and
performance tradeoffs in C++.

## Implemented Data Structures

- DynamicArray
- LinkedList
- Stack
- Queue
- HashMap
- BinarySearchTree

## Build Requirements

- C++17 compatible compiler
- Tested with `clang++` on macOS

## Unit Tests

Unit tests verify correctness and basic functionality.

```
clang++ -std=c++17 -O2 -Wall -Wextra -Wpedantic test.cpp DynamicArray.cpp Stack.cpp
LinkedList.cpp Queue.cpp HashMap.cpp BinarySearchTree.cpp -o test && ./test
```

## Performance Tests

Performance tests measure runtime behavior and compare against C++ Standard Library equivalents.

```
clang++ -std=c++17 -O2 -Wall -Wextra -Wpedantic bench.cpp DynamicArray.cpp Stack.cpp
LinkedList.cpp Queue.cpp HashMap.cpp BinarySearchTree.cpp -o bench && ./bench
```

## Performance Results

Performance tests were run on macOS using `clang++ -O2`.
Each test reports the best time over multiple trials.
Results vary by machine.

| Data Structure   | Operation                         | Custom  | C++ Standard Library | Faster than STL? |
|------------------|-----------------------------------|---------|----------------------|------------------|
| DynamicArray     | push_back (3,000,000 elements)    | ~14  ms | ~5   ms              | No               |
| LinkedList       | push_back + pop_front (3,000,000) | ~152 ms | ~169 ms              | Yes              |
| HashMap          | insert + get (3,000,000)          | ~332 ms | ~372 ms              | Yes              |
| BinarySearchTree | insert + contains (600,000)       | ~228 ms | ~236 ms              | Yes              |

## Rationale for Performance Differences

DynamicArray: std::vector uses memcpy while my DynamicArray does not, presumably resulting in higher speeds.
LinkedList: std::list is a doubly-linked list while my LinkedList is a singly-linked list with a tail pointer, presumably resulting in slower speeds from more operations.
HashMap: std::unordered_map has a more complex hash function than my HashMap, presumably resulting in slower speeds from more operations.
BinarySearchTree: std::set is a balanced binary search tree while my BinarySearchTree is an unbalanced binary search tree, presumably resulting in slower speeds from more operations.
