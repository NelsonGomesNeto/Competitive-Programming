#include <bits/stdc++.h>
#define DEBUG if (1)
#define lli long long int
#define ldouble long double

const int kDirectionCount = 4;
const int di[kDirectionCount] = {-1, 0, 1, 0};
const int dj[kDirectionCount] = {0, 1, 0, -1};

struct Problem {
  std::vector<std::string> map;
  int n, m;

  bool Valid(const int x, const int limit) { return x >= 0 && x < limit; }
  void Guard(const int si, const int sj) {
    int i = si, j = sj, d = 0;
    while (true) {
      map[i][j] = 'X';

      const int ni = i + di[d], nj = j + dj[d];
      if (!Valid(ni, n) || !Valid(nj, m)) break;

      if (map[ni][nj] == '#') {
        if (++d >= kDirectionCount) d = 0;
      } else {
        i = ni, j = nj;
      }
    }
  }

  void Solve() {
    for (std::string line; std::getline(std::cin, line) && !line.empty();) {
      map.push_back(line);
    }
    n = map.size(), m = map[0].size();

    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        if (map[i][j] == '^') Guard(i, j);

    int ans = 0;
    for (const auto& line : map) {
      DEBUG std::cout << line << "\n";
      for (const char c : line) ans += c == 'X';
    }
    DEBUG std::cout << "-------------\n";
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
