#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kDi[8] = {2, 1, -1, -2, -2, -1, 1, 2};
const int kDj[8] = {1, 2, 2, 1, -1, -2, -2, -1};

struct TestCase {
  int n, m;
  std::vector<std::pair<int, int>> pieces;
  std::set<std::pair<int, int>> attacked;

  void Add(const int i, const int j) {
    for (int d = 0; d < 8; ++d) {
      const int ni = i + kDi[d], nj = j + kDj[d];
      if (ni < 0 || ni >= n || nj < 0 || nj >= n) continue;
      attacked.emplace(ni, nj);
    }
  }

  bool Run() {
    if (!(std::cin >> n >> m)) return false;
    pieces.resize(m);
    for (auto& [i, j] : pieces) {
      std::cin >> i >> j;
      --i, --j;
      attacked.emplace(i, j);
    }

    lli ans = (lli)n * n;
    for (const auto& [i, j] : pieces) {
      Add(i, j);
    }
    ans -= attacked.size();

    std::cout << ans << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
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
