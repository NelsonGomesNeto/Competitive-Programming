#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n;
  std::vector<std::string> city;

  std::vector<std::vector<int>> memo;
  int Solve(int j0 = 0, int j1 = 0) {
    DEBUG std::cout << "curr: " << j0 << " | " << j1 << "\n";
    if (j0 >= n && j1 >= n) {
      return 0;
    }

    const int delta = 5 + j0 - j1;
    assert(delta >= 0 && delta < 10);
    int& ans = memo[j0][delta];
    if (ans != -1) return ans;

    auto GetResult = [&](const int nj0, const int nj1) -> int {
      int a_sum = 0;
      for (int i = j0; i < nj0; ++i) {
        assert(i < n);
        a_sum += city[0][i] == 'A';
      }
      for (int i = j1; i < nj1; ++i) {
        assert(i < n);
        a_sum += city[1][i] == 'A';
      }
      return a_sum >= 2;
    };
    // Line above
    if (j0 <= j1 && j0 + 3 <= n) {
      ans = std::max(ans, Solve(j0 + 3, j1) + GetResult(j0 + 3, j1));
    }
    // Line below
    if (j1 <= j0 && j1 + 3 <= n) {
      ans = std::max(ans, Solve(j0, j1 + 3) + GetResult(j0, j1 + 3));
    }
    // ## | #
    // #  | ##
    if (j0 == j1) {
      if (j0 + 2 <= n && j1 + 1 <= n)
        ans = std::max(ans, Solve(j0 + 2, j1 + 1) + GetResult(j0 + 2, j1 + 1));
      if (j0 + 1 <= n && j1 + 2 <= n)
        ans = std::max(ans, Solve(j0 + 1, j1 + 2) + GetResult(j0 + 1, j1 + 2));
    }
    // ##
    //  #
    if (j0 + 1 == j1) {
      if (j0 + 2 <= n && j1 + 1 <= n)
        ans = std::max(ans, Solve(j0 + 2, j1 + 1) + GetResult(j0 + 2, j1 + 1));
    }
    //  #
    // ##
    if (j0 == j1 + 1) {
      if (j0 + 1 <= n && j1 + 2 <= n)
        ans = std::max(ans, Solve(j0 + 1, j1 + 2) + GetResult(j0 + 1, j1 + 2));
    }

    return ans;
  }

  int TestCaseSolve() {
    std::cin >> n;
    city.resize(2);
    for (std::string& s : city) std::cin >> s;
    DEBUG std::cout << "\t" << city[0] << "\n\t" << city[1] << "\n";

    memo.resize(n + 1, std::vector<int>(10, -1));
    int ans = Solve();
    return ans;
  }
};
TestCase test_case;

int main() {
  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    const auto ans = test_case.TestCaseSolve();
    std::cout << ans << "\n";
  }
  return 0;
}
