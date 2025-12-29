// Performance tests for data structures libary
// clang++ -std=c++17 -O2 -Wall -Wextra -Wpedantic bench.cpp DynamicArray.cpp \
// Stack.cpp LinkedList.cpp Queue.cpp HashMap.cpp BinarySearchTree.cpp -o bench && ./bench

#include "DynamicArray.h"
#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include "HashMap.h"
#include "BinarySearchTree.h"

#include <iostream>
#include <cstddef>
#include <chrono>
#include <random>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <unordered_map>
#include <set>

using Clock = std::chrono::steady_clock;

static volatile double sink_double{0.0};
static volatile int sink_int{0};

template <typename F>
long long time_ms(F&& f) {
    auto start{Clock::now()};
    f();
    auto end{Clock::now()};

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

static std::vector<int> make_random_ints(std::size_t n, int lo, int hi, unsigned seed = 12345) {
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(lo, hi);
    std::vector<int> v;
    v.reserve(n);

    for (std::size_t i{0}; i < n; ++i) {
        v.push_back(dist(rng));
    }

    return v;
}

static std::vector<double> make_random_doubles(std::size_t n, double lo, double hi, unsigned seed = 12345) {
    std::mt19937 rng(seed);
    std::uniform_real_distribution<double> dist(lo, hi);
    std::vector<double> v;
    v.reserve(n);

    for (std::size_t i{0}; i < n; ++i) {
        v.push_back(dist(rng));
    }

    return v;
}

int main() {
    const std::size_t N{3000000}; // Adjust as needed
    const int trials{5};
    auto rands_d = make_random_doubles(N, -1e6, 1e6);
    auto rands_i = make_random_ints(N, -1000000, 1000000);
    std::cout << "N = " << N << " trials = " << trials << "\n\n";

    // DynamicArray vs. std::vector (push_back)
    {
        long long best_my{1LL << 62};
        long long best_stl{1LL << 62};

        for (int t{0}; t < trials; ++t) {
            best_my = std::min(best_my, time_ms([&]{
                DynamicArray a;

                for (std::size_t i{0}; i < N; ++i) {
                    a.push_back(rands_d[i]);
                }

                sink_double = a.back();
            }));

            best_stl = std::min(best_stl, time_ms([&]{
                std::vector<double> v;

                for (std::size_t i{0}; i < N; ++i) {
                    v.push_back(rands_d[i]);
                }

                sink_double = v.back();
            }));
        }

        std::cout << "[push_back N] DynamicArray: " << best_my << " ms" << " | std::vector: " << best_stl << " ms\n";
    }

    // LinkedList vs. std::list (push_back + pop_front)
    {
        long long best_my{1LL << 62};
        long long best_stl{1LL << 62};

        for (int t{0}; t < trials; ++t) {
            best_my = std::min(best_my, time_ms([&]{
                LinkedList l;

                for (std::size_t i{0}; i < N; ++i) {
                    l.push_back(rands_d[i]);
                }

                for (std::size_t i = 0; i < N; ++i) {
                    l.pop_front();
                }

                sink_double = (l.empty() ? 0.0 : l.front());
            }));

            best_stl = std::min(best_stl, time_ms([&]{
                std::list<double> l;

                for (std::size_t i{0}; i < N; ++i) {
                    l.push_back(rands_d[i]);
                }

                for (std::size_t i{0}; i < N; ++i) {
                    l.pop_front();
                }

                sink_double = (l.empty() ? 0.0 : l.front());
            }));
        }

        std::cout << "[push_back + pop_front N] LinkedList: " << best_my << " ms" << " | std::list: " << best_stl << " ms\n";
    }

    // HashMap vs. std::unordered_map (insert + get)
    {
        const std::size_t M{N};
        long long best_my{1LL << 62};
        long long best_stl{1LL << 62};

        for (int t{0}; t < trials; ++t) {
            best_my = std::min(best_my, time_ms([&]{
                HashMap m;

                for (std::size_t i{0}; i < M; ++i) {
                    m.insert(rands_i[i], (int)i);
                }

                int out{0};
                int hits{0};

                for (std::size_t i{0}; i < M; ++i) {
                    if (m.get(rands_i[i], out)) {
                        hits += out;
                    }
                }

                sink_int = hits;
            }));

            best_stl = std::min(best_stl, time_ms([&]{
                std::unordered_map<int,int> m;

                for (std::size_t i{0}; i < M; ++i) {
                    m[rands_i[i]] = (int)i;
                }

                int hits{0};
                
                for (std::size_t i{0}; i < M; ++i) {
                    auto it{m.find(rands_i[i])};

                    if (it != m.end()) {
                        hits += it->second;
                    }
                }

                sink_int = hits;
            }));
        }

        std::cout << "[insert + get M] HashMap: " << best_my << " ms" << " | std::unordered_map: " << best_stl << " ms\n";
    }

    // BinarySearchTree vs. std::set (insert + contains)
    {
        const std::size_t M{N / 5};
        long long best_my{1LL << 62};
        long long best_stl{1LL << 62};

        for (int t{0}; t < trials; ++t) {
            best_my = std::min(best_my, time_ms([&]{
                BinarySearchTree bst;

                for (std::size_t i{0}; i < M; ++i) {
                    bst.insert(rands_d[i]);
                }

                int hits{0};

                for (std::size_t i{0}; i < M; ++i) {
                    if (bst.contains(rands_d[i])) {
                        ++hits;
                    }
                }

                sink_int = hits;
            }));

            best_stl = std::min(best_stl, time_ms([&]{
                std::set<double> s;

                for (std::size_t i{0}; i < M; ++i) {
                    s.insert(rands_d[i]);
                }

                int hits{0};

                for (std::size_t i{0}; i < M; ++i) {
                    if (s.find(rands_d[i]) != s.end()) {
                        ++hits;
                    }
                }

                sink_int = hits;
            }));
        }

        std::cout << "[insert + contains M] BST: " << best_my << " ms" << " | std::set: " << best_stl << " ms\n";
    }

    std::cout << "\n(sink_double = " << sink_double << ", sink_int = " << sink_int << ")\n";
}

