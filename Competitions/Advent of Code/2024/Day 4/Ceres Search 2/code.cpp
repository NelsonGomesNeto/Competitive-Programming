#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const std::string kMas = "MAS";

const int kDirections = 4;
const int di[4] = {-1, -1, 1, 1};
const int dj[4] = {-1, 1, -1, 1};

struct Problem {
  int n, m;
  std::vector<std::string> table;

  bool Valid(const int x, const int limit) { return x >= 0 && x < limit; }

  int Search(const int si, const int sj) {
    if (table[si][sj] != kMas[1]) return 0;

    int cnt = 0;
    for (int d = 0; d < kDirections; ++d) {
      auto Check = [&](const std::string& target) -> bool {
        for (int i = si - di[d], j = sj - dj[d], k = 0; k < target.size();
             ++k, i += di[d], j += dj[d]) {
          if (!Valid(i, n) || !Valid(j, m) || table[i][j] != target[k]) {
            return false;
          }
        }
        return true;
      };

      cnt += Check(kMas);
    }
    return cnt == 2;
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
