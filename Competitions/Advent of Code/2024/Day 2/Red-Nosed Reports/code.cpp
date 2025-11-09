#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct Problem {
  std::vector<std::vector<int>> reports;

  void Solve() {
    for (std::string line; std::getline(std::cin, line);) {
      std::istringstream sin(line);
      reports.emplace_back();
      std::vector<int>& levels = reports.back();
      for (int a; sin >> a;) {
        levels.push_back(a);
      }
    }

    int ans = 0;
    for (const auto& levels : reports) {
      if (levels.size() <= 1) {
        ++ans;
        continue;
      }

      bool increasing = levels[0] < levels[1], valid = true;
      for (int i = 1; valid && i < levels.size(); ++i) {
        if (increasing)
          valid &= levels[i - 1] < levels[i];
        else
          valid &= levels[i - 1] > levels[i];

        const int delta = std::abs(levels[i - 1] - levels[i]);
        valid &= delta <= 3;
      }
      ans += valid;
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
