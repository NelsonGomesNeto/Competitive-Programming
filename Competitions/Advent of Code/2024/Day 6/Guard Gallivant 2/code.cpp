#include <bits/stdc++.h>
#define DEBUG if (1)
#define lli long long int
#define ldouble long double

const int kDirectionCount = 4;
const int di[kDirectionCount] = {-1, 0, 1, 0};
const int dj[kDirectionCount] = {0, 1, 0, -1};
bool once = false;

struct Problem {
  std::vector<std::string> map, filled_map;
  std::vector<std::vector<std::vector<int>>> visited;
  int n, m;
  int si, sj;

  bool Valid(const int x, const int limit) { return x >= 0 && x < limit; }

  int iteration_cnt;
  bool GuardCycles(const bool clear = false) {
    auto MarkStep = [&](const int i, const int j, const int d) {
      visited[i][j][d] = iteration_cnt;
      if (filled_map[i][j] == '^') return;

      if (clear) {
        filled_map[i][j] = map[i][j];
      } else {
        const char new_mark = d & 1 ? '-' : '|';
        if (filled_map[i][j] == '.')
          filled_map[i][j] = new_mark;
        else if (filled_map[i][j] != new_mark)
          filled_map[i][j] = '+';
      }
    };

    auto Bfs = [&]() {
      int i = si, j = sj, d = 0;
      while (true) {
        if (visited[i][j][d] == iteration_cnt) return true;
        MarkStep(i, j, d);

        const int ni = i + di[d], nj = j + dj[d];
        if (!Valid(ni, n) || !Valid(nj, m)) break;

        if (map[ni][nj] == '#' || map[ni][nj] == 'O') {
          if (++d >= kDirectionCount) d = 0;
        } else {
          i = ni, j = nj;
        }
      }
      return false;
    };
    const bool res = Bfs();
    ++iteration_cnt;
    return res;
  }

  bool Obstruct(const int oi, const int oj) {
    map[oi][oj] = 'O';
    filled_map = map;

    bool cycles = GuardCycles();
    // Interestingly, it's MUCH faster to do `filled_map = map` than to traceback
    // remove those.
    // GuardCycles(/*clear=*/true);

    DEBUG {
      if (!once && cycles) {
        for (const auto& line : filled_map) {
          std::cout << line << "\n";
        }
        once = true;
      }
    }

    map[oi][oj] = filled_map[oi][oj] = '.';

    return cycles;
  }

  void Solve() {
    for (std::string line; std::getline(std::cin, line) && !line.empty();) {
      map.push_back(line);
    }
    n = map.size(), m = map[0].size();
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        if (map[i][j] == '^') si = i, sj = j;
    filled_map = map;

    // This was the best optimization (6s to 400ms).
    iteration_cnt = 0;
    visited = std::vector<std::vector<std::vector<int>>>(
        n, std::vector<std::vector<int>>(
               m, std::vector<int>(kDirectionCount, -1)));

    int ans = 0;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        if (map[i][j] == '.') {
          ans += Obstruct(i, j);
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
