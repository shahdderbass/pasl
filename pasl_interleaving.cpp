#include <iostream>
#include <vector>
#include <mutex>
// include PASL headers
#include "sched/native.hpp"

std::mutex m;
std::vector<std::string> logv;

void logmsg(const std::string& s) {
    std::lock_guard<std::mutex> g(m);
    logv.push_back(s);
}

int main() {
    logv.clear();

    const int YOUR_N = 1000000;

    pasl::sched::native::fork2(
        // Branch A
        [&] {
            logmsg("A1");
            for (volatile int i = 0; i < YOUR_N; i++) {}
            logmsg("A2");
        },
        // Branch B
        [&] {
            logmsg("B1");
            for (volatile int i = 0; i < YOUR_N; i++) {}
            logmsg("B2");
        }
    );

    // join point
    for (auto &s : logv)
        std::cout << s << " ";
    std::cout << "\n";

    return 0;
}

