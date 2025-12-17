#include <iostream>
#include <vector>
// Include PASL headers
#include "sched/native.hpp"

void map_incr_rec(const long* src, long* dst, long lo, long hi) {
    long n = hi - lo;
    if (n == 0) return;
    if (n == 1) {
        dst[lo] = src[lo] + 1;
        return;
    }

    long mid = (lo + hi) / 2;

    // Process both halves in parallel using fork2
    pasl::sched::native::fork2(
        [&] {
            map_incr_rec(src, dst, lo, mid);
        },
        [&] {
            map_incr_rec(src, dst, mid, hi);
        }
    );
}

int main() {
    const long n = 8;
    std::vector<long> xs(n), ys(n);

    for (long i = 0; i < n; i++)
        xs[i] = i;

    map_incr_rec(xs.data(), ys.data(), 0, n);

    for (long i = 0; i < n; i++)
        std::cout << ys[i] << " ";
    std::cout << std::endl;

    return 0;
}

