#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kSteps = 15;

const int di[4] = {0, 1, -1, 0};
const int dj[4] = {1, 0, 0, -1};
struct Pos {
  int i, j;
  Pos NextDir(const int d) { return Pos{i + di[d], j + dj[d]}; }
};
struct Map {
  Pos start_pos;
  int n, m;
  std::vector<std::string> map;

  void Build(const std::vector<std::string>& new_map) {
    map = new_map;
    n = map.size(), m = map[0].size();
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (map[i][j] == 'S') {
          start_pos = Pos{i, j};
          map[i][j] = '.';
        }
      }
    }
  }

  friend std::istream& operator>>(std::istream& isin, Map& m) {
    std::vector<std::string> map;
    for (std::string line; std::getline(isin, line);) {
      map.push_back(line);
    }
    m.Build(map);
    return isin;
  }
  friend std::ostream& operator<<(std::ostream& osout, const Map& m) {
    for (const std::string& line : m.map) {
      osout << line << "\n";
    }
    return osout;
  }

  bool ValidPos(const Pos p) {
    return p.i >= 0 && p.i < n && p.j >= 0 && p.j < m && map[p.i][p.j] == '.';
  }

  std::vector<std::vector<std::vector<bool>>> memo;
  int Walk(const int max_steps) {
    memo.resize(
        n, std::vector<std::vector<bool>>(m, std::vector<bool>(kSteps, false)));

    std::queue<std::pair<Pos, int>> q;
    q.emplace(start_pos, 0);
    while (!q.empty()) {
      auto [p, steps] = q.front();
      q.pop();
      if (steps == max_steps) {
        map[p.i][p.j] = 'O';
        continue;
      }
      if (memo[p.i][p.j][steps]) {
        continue;
      }
      memo[p.i][p.j][steps] = true;

      for (int d = 0; d < 4; ++d) {
        Pos np = p.NextDir(d);
        if (!ValidPos(np)) continue;
        q.emplace(np, steps + 1);
      }
    }

    int reachable = 0;
    for (const std::string line : map) {
      for (const char c : line) {
        reachable += c == 'O';
      }
    }
    map[start_pos.i][start_pos.j] = 'S';
    return reachable;
  }
};
Map map;

int main() {
  std::cin >> map;

  int reachable = map.Walk(kSteps);

  std::cout << map;
  std::cout << reachable << "\n";

  return 0;
}