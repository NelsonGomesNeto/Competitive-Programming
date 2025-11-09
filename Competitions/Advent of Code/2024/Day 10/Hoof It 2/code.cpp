#include <bits/stdc++.h>
#define DEBUG if (1)
#define lli long long int
#define ldouble long double

const char kStart = '0', kEnd = '9';
const int kDirections = 4;
const int kDi[kDirections] = {-1, 0, 1, 0};
const int kDj[kDirections] = {0, 1, 0, -1};

struct Problem {
  int n, m;
  std::vector<std::string> map;

  struct Pos {
    int i, j;
    Pos Move(const int d) const { return Pos{i + kDi[d], j + kDj[d]}; }
  };
  char Height(const Pos& p) { return map[p.i][p.j]; }
  bool Valid(const int x, const int limit) { return x >= 0 && x < limit; }
  bool Valid(const Pos& p) { return Valid(p.i, n) && Valid(p.j, m); }

  int Hike(const Pos& start) {
    int ans = 0;
    std::queue<Pos> q;
    q.push(start);
    while (!q.empty()) {
      const Pos curr = q.front();
      q.pop();

      if (Height(curr) == kEnd) {
        ++ans;
        continue;
      }

      for (int d = 0; d < kDirections; ++d) {
        const Pos nxt = curr.Move(d);
        if (!Valid(nxt) || Height(curr) + 1 != Height(nxt)) continue;
        q.push(nxt);
      }
    }
    return ans;
  }

  void Solve() {
    for (std::string line; std::getline(std::cin, line) && !line.empty();)
      map.push_back(line);
    n = map.size(), m = map[0].size();

    int ans = 0;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        if (map[i][j] != kStart) continue;

        const int cnt = Hike({i, j});
        DEBUG std::cout << "\t" << i << " " << j << " | " << cnt << "\n";
        ans += cnt;
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
