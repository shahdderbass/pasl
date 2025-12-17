#include <iostream>
#include <atomic>
// include PASL headers (same as your lecture environment)
#include "sched/native.hpp"

int main() {
  long b1 = 0, b2 = 0;
  long j  = 0;

  // TODO: Replace this with PASL fork2 exactly like lecture style
  // fork2([&]{ ... }, [&]{ ... });

	pasl::sched::native::fork2(
        [&] {
            b1 = 1;   // Branch 1
        },
        [&] {
            b2 = 2;   // Branch 2
        }
    )


  // join point
  j = b1 + b2;

  std::cout << "b1=" << b1 << " b2=" << b2 << " j=" << j << "\n";
  return 0;
}

