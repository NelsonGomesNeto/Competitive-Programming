#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct Vec {
  int i, j;
  Vec Add(const Vec& other) const { return Vec{i + other.i, j + other.j}; }
  bool operator==(const Vec& other) const {
    return i == other.i && j == other.j;
  }
  friend std::ostream& operator<<(std::ostream& out, const Vec& v) {
    return out << "(" << v.i << ", " << v.j << ")";
  }
};
const std::vector<Vec> kDirections{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

struct Problem {
  int n, m;
  int minimum_saved;
  std::vector<std::string> map;
  Vec start_pos, end_pos;

  bool Valid(const int x, const int limit) { return x >= 0 && x < limit; }
  bool Valid(const Vec& pos) {
    return Valid(pos.i, n) && Valid(pos.j, m) && map[pos.i][pos.j] != '#';
  }

  std::vector<std::vector<bool>> visited;
  int Bfs() {
    for (auto& line : visited) std::ranges::fill(line, false);
    std::queue<std::pair<Vec, int>> q;
    q.emplace(start_pos, 0);
    while (!q.empty()) {
      const auto [pos, d] = q.front();
      q.pop();

      if (visited[pos.i][pos.j]) continue;
      visited[pos.i][pos.j] = true;

      if (pos == end_pos) return d;

      for (const auto& dir : kDirections) {
        const Vec nxt_pos = pos.Add(dir);
        if (!Valid(nxt_pos) || visited[nxt_pos.i][nxt_pos.j]) continue;
        q.emplace(nxt_pos, d + 1);
      }
    }
    return -1;
  }

  std::map<int, int> TryAllCheats() {
    std::map<int, int> count_by_steps;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        if (map[i][j] != '#') continue;

        map[i][j] = '.';
        const int shotest_path = Bfs();
        count_by_steps[shotest_path]++;
        map[i][j] = '#';
      }
    return count_by_steps;
  }

  void Solve() {
    std::cin >> minimum_saved;
    std::cin.ignore(1);
    for (std::string line; std::getline(std::cin, line);) {
      map.push_back(line);
    }
    n = map.size(), m = map[0].size();
    visited.resize(n, std::vector<bool>(m, false));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (map[i][j] == 'S') start_pos = {i, j};
        if (map[i][j] == 'E') end_pos = {i, j};
      }
    }

    std::cout << "nxm: " << n << " " << m << "\n";
    for (const auto& line : map) std::cout << line << "\n";
    std::cout << "minimum_saved: " << minimum_saved << "\n";
    std::cout << "start_pos: " << start_pos << "\n";
    std::cout << "end_pos: " << end_pos << "\n";

    const int fastest_path = Bfs();
    std::cout << "fastest_path: " << fastest_path << "\n";

    std::map<int, int> count_by_steps = TryAllCheats();

    int ans = 0;
    for (const auto& [steps, count] : count_by_steps) {
      const int saved = fastest_path - steps;
      if (saved == 0) continue;
      std::cout << count << " " << saved << "\n";
      if (saved < minimum_saved) continue;
      ans += count;
    }
    std::println("ans: {}", ans);
  }
};
Problem problem;

int main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);

  problem.Solve();

  return 0;
}
