#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct Problem {
  std::vector<int> a, b;

  void Solve() {
    int ai, bi;
    while (std::cin >> ai >> bi) {
      a.push_back(ai), b.push_back(bi);
    }

    std::ranges::sort(a), std::ranges::sort(b);

    int ans = 0;
    for (const auto [ai, bi] : std::ranges::zip_view(a, b)) {
      ans += std::abs(ai - bi);
    }
    std::println("ans: {}", ans);
  }
};
Problem problem;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  problem.Solve();

  return 0;
}
