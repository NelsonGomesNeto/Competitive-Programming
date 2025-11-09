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

      for (const bool increasing : std::vector<bool>{false, true}) {
        const auto Check = [&](const int to_skip) -> int {
          const int start = to_skip == 0 ? 1 : 0;
          for (int i = start, j = start + 1; j < levels.size(); ++i, ++j) {
            if (j == to_skip) ++j;
            if (j >= levels.size()) break;
            if (i == to_skip) ++i;
            const int a = levels[i], b = levels[j];

            bool safe = true;
            if (increasing)
              safe &= a < b;
            else
              safe &= a > b;
            const int delta = std::abs(a - b);
            safe &= delta <= 3;

            if (!safe) return j;
          }
          return levels.size();
        };

        bool valid = false;
        const int furthest_pos = Check(-1);
        if (furthest_pos == levels.size()) {
          valid = true;
        } else {
          valid = Check(furthest_pos) == levels.size() ||
                  Check(furthest_pos - 1) == levels.size();
        }

        if (valid) {
          ++ans;
          break;
        }
      }
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
