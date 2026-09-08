#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int

int main() {
  const uint a = 0b0011;

  std::println("{} {:b} | {} {} {} {}", a, a, std::countr_zero(a),
               std::countl_zero(a), std::countr_one(a), std::countl_one(a));

  return 0;
}
