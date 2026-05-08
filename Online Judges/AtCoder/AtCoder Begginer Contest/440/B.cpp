#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n;
  std::vector<int> a;
  bool Run() {
    if (!(std::cin >> n)) return false;
    a.resize(n);
    std::vector<std::pair<int, int>> horses;
    horses.reserve(n);
    for (auto [i, ai] : a | std::views::enumerate) {
      std::cin >> ai;
      horses.emplace_back(ai, i + 1);
    }
    std::ranges::sort(horses);
    std::println("{} {} {}", horses[0].second, horses[1].second,
                 horses[2].second);
    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
