#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const std::string kTarget = "XMAS";

const int di[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dj[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

struct Problem {
  int n, m;
  std::vector<std::string> table;

  bool Valid(const int x, const int limit) {
    return x >= 0 && x < limit;
  }

  int Search(const int si, const int sj) {
    if (table[si][sj] != kTarget[0]) return 0;

    int cnt = 0;
    for (int d = 0; d < 8; ++d) {
      bool valid = true;

      for (int i = si, j = sj, k = 1; k < kTarget.size(); ++k) {
        i += di[d], j += dj[d];
        if (!Valid(i, n) || !Valid(j, m) || table[i][j] != kTarget[k]) {
          valid = false;
          break;
        }
      }
      if (!valid) continue;

      ++cnt;
    }
    return cnt;
  }

  void Solve() {
    for (std::string line; std::cin >> line;) {
      table.push_back(line);
    }
    n = table.size(), m = table[0].size();

    int ans = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        ans += Search(i, j);
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
