#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, m;
  std::vector<int> a, b;
  std::vector<int> to_try;

  std::vector<std::vector<int>> memo;
  int GetValue(const int i, const int flipi) {
    return flipi == to_try.size() ? a[i] : to_try[flipi] - a[i];
  }
  int Solve(int i, int flipi) {
    if (i == a.size()) {
      return true;
    }
    int& ans = memo[i][flipi];
    if (ans != -1) return ans;

    ans = false;
    for (int j = 0; j <= to_try.size(); ++j) {
      if (i == 0 || GetValue(i - 1, flipi) <= GetValue(i, j))
        ans = std::max(ans, Solve(i + 1, j));
    }

    return ans;
  }

  bool Run() {
    if (!(std::cin >> n >> m)) return false;
    a.resize(n), b.resize(m);
    for (auto& ai : a) std::cin >> ai;
    for (auto& bi : b) std::cin >> bi;
    std::sort(b.begin(), b.end());
    b.resize(std::distance(b.begin(), std::unique(b.begin(), b.end())));
    a.resize(std::distance(a.begin(), std::unique(a.begin(), a.end())));

    to_try.clear();
    auto Add = [&to_try = to_try](const std::vector<int>& lol) {
      for (int j = 0, end = std::min((int)lol.size(), 50); j < end; ++j) {
        to_try.push_back(lol[j]),
            to_try.push_back(lol[(int)lol.size() - j - 1]);
      }
    };
    Add(b);

    const auto [mini_it, maxi_it] = std::minmax_element(a.begin(), a.end());
    const int mini = *mini_it, maxi = *maxi_it;
    std::vector<int> b_filtered;
    for (const auto bi : b) {
      if (bi <= mini || bi >= maxi) b_filtered.push_back(bi);
    }
    Add(b_filtered);

    std::sort(to_try.begin(), to_try.end());
    to_try.resize(std::distance(to_try.begin(),
                                std::unique(to_try.begin(), to_try.end())));

    memo.resize(a.size(), std::vector<int>(to_try.size() + 1, -1));
    bool can = Solve(0, 0);

    std::cout << (can ? "YES" : "NO") << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    test_case.Run();
  }

  return 0;
}
