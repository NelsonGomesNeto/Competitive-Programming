#include <bits/stdc++.h>

int main() {
  std::random_device rd;
  std::mt19937 g(rd());

  std::vector<int> a(10);
  std::ranges::iota(a, 1);
  std::println("a        : {}", a);
  std::ranges::shuffle(a, g);
  std::println("shuffle a: {}", a);

  return 0;
}