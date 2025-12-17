#include <iostream>
#include <chrono>
// Include PASL headers
#include "sched/native.hpp"

long fib_seq(long n) {
    if (n < 2) return n;
    return fib_seq(n - 1) + fib_seq(n - 2);
}

long fib_par(long n) {
    if (n < 2) return n;

    long a, b;

    // Parallel recursive calls using fork2
    pasl::sched::native::fork2(
        [&] {
            a = fib_par(n - 1);
        },
        [&] {
            b = fib_par(n - 2);
        }
    );

    return a + b;
}

int main() {
    long n = 25;

    auto t1 = std::chrono::high_resolution_clock::now();
    long r1 = fib_seq(n);
    auto t2 = std::chrono::high_resolution_clock::now();
    long r2 = fib_par(n);
    auto t3 = std::chrono::high_resolution_clock::now();

    auto seq_time =
        std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    auto par_time =
        std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count();

    std::cout << "n = " << n
              << ", fib_seq = " << r1
              << ", time = " << seq_time << " ms" << std::endl;

    std::cout << "n = " << n
              << ", fib_par = " << r2
              << ", time = " << par_time << " ms" << std::endl;

    return 0;
}

