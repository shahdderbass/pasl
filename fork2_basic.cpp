#include <iostream>
#include <atomic>
// include PASL headers
#include "sched/native.hpp"

int main() {
    long b1 = 0, b2 = 0;
    long j  = 0;

    pasl::sched::native::fork2(
        // Branch 1
        [&] {
            b1 = 1;
        },
        // Branch 2
        [&] {
            b2 = 2;
        }
    );

    // join point
    j = b1 + b2;

    std::cout << "b1=" << b1 << " b2=" << b2 << " j=" << j << "\n";
    return 0;
}

