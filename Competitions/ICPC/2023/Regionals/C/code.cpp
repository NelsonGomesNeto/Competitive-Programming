#include <bits/stdc++.h>

const int kHashVersions = 5;
std::mt19937 random_gen;

struct TestCase {
  int n, k;
  std::vector<int> c;
  std::array<std::vector<int>, kHashVersions> cversions;
  std::array<std::vector<int>, kHashVersions> accs;

  int BinarySearchFromI(const int start) {

  }

  bool Run() {
    if (!(std::cin >> n >> k)) return false;
    c.resize(n);
    for (int& ci : c) {
      std::cin >> ci;
      --ci;
    }

    // Precalc "hash" versions.
    std::vector<int> mapping(k);
    std::ranges::iota(mapping, 0);
    for (auto [cv, acc] : std::views::zip(cversions, accs)) {
      std::ranges::shuffle(mapping, random_gen);
      cv = c;
      acc[0] = 0;
      for (int i = 0; i < n; ++i) {
        cv[i] = mapping[cv[i]];
        acc[i + 1] = acc[i] + cv[i];
      }
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
      ans = BinarySearchFromI(i);
    }
    std::println("{}", ans);

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::random_device rd;
  random_gen = std::mt19937(rd());

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
