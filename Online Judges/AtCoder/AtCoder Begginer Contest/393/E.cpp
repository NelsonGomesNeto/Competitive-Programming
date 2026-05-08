#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kMaxA = 1e6;
std::vector<std::vector<int>> divisors;
void InitDivisors() {
  divisors.resize(kMaxA + 1, std::vector<int>{});
  for (int i = 1; i <= kMaxA; ++i) {
    for (int j = 1; i * j <= kMaxA; ++j) {
      divisors[i * j].push_back(i);
    }
  }
}

struct TestCase {
  int n, k;
  std::vector<int> a;
  std::vector<int> multiples;
  bool Run() {
    if (!(std::cin >> n >> k)) return false;
    a.resize(n);
    for (auto& ai : a) std::cin >> ai;

    multiples.resize(kMaxA + 1, 0);
    for (const auto ai : a) {
      for (const int d : divisors[ai]) {
        ++multiples[d];
      }
    }

    for (int i = 0; i < n; ++i) {
      const int ai = a[i];
      for (auto it = divisors[ai].rbegin(); it != divisors[ai].rend(); ++it) {
        const int div = *it;
        if (multiples[div] < k) continue;
        std::cout << div << "\n";
        break;
      }
    }

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  InitDivisors();

  // int test_cases;
  // std::cin >> test_cases;
  // for (int t = 1; t <= test_cases; ++t) {
  //   test_case = TestCase{};
  //   test_case.Run();
  // }

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
