#include <bits/stdc++.h>
#define lli long long int

int main() {
  std::random_device rd;
  std::mt19937 g(rd());

  std::vector<int> a(10);
  std::ranges::iota(a, 1);
  std::println("a        : {}", a);
  std::ranges::shuffle(a, g);
  std::println("shuffle a: {}", a);

  // g() is actually an uint32_t.
  const int b = g();
  std::println("b: {}", b);

  std::mt19937_64 g64(rd());
  // g64() is actually an uint64_t
  const lli c = g64();
  std::println("c: {}", c);

  return 0;
}