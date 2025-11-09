#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct Vec {
  int i, j;
  Vec Add(const Vec& other) const { return Vec{i + other.i, j + other.j}; }
  int ManhattanDistance(const Vec& other) const {
    return std::abs(i - other.i) + std::abs(j - other.j);
  }
  bool operator==(const Vec& other) const {
    return i == other.i && j == other.j;
  }
  friend std::ostream& operator<<(std::ostream& out, const Vec& v) {
    return out << "(" << v.i << ", " << v.j << ")";
  }
};
const std::vector<Vec> kDirections{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const Vec kNil{-1, -1};
const int kInf = 1e7;

struct Problem {
  int n, m;
  int minimum_saved;
  std::vector<std::string> map;
  Vec start_pos, end_pos;
  int fastest_path = -1;

  bool Valid(const int x, const int limit) { return x >= 0 && x < limit; }
  bool Valid(const Vec& pos) {
    return Valid(pos.i, n) && Valid(pos.j, m) && map[pos.i][pos.j] != '#';
  }

  std::vector<std::vector<std::vector<bool>>> visited;
  int Bfs(const Vec& cheat_start, const Vec& cheat_end) {
    for (auto& line : visited)
      for (auto& cols : line) std::ranges::fill(cols, false);

    std::queue<std::tuple<Vec, int, bool>> q;
    q.emplace(start_pos, 0, false);
    while (!q.empty()) {
      const auto [pos, d, cheated] = q.front();
      q.pop();

      if (cheat_start.i != -1 && fastest_path - d < minimum_saved) continue;

      if (visited[pos.i][pos.j][cheated]) continue;
      visited[pos.i][pos.j][cheated] = true;

      if (pos == end_pos) return d;

      for (const auto& dir : kDirections) {
        const Vec nxt_pos = pos.Add(dir);
        if (!Valid(nxt_pos) || visited[nxt_pos.i][nxt_pos.j][cheated]) continue;
        q.emplace(nxt_pos, d + 1, cheated);
      }
      if (!cheated && pos == cheat_start) {
        q.emplace(cheat_end, d + 1, true);
      }
    }
    return kInf;
  }

  std::map<int, int> TryAllCheats() {
    std::map<int, int> count_by_steps;
    std::vector<Vec> all_valid_positions;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        if (map[i][j] != '#') all_valid_positions.emplace_back(i, j);

    const int todo =
        ((int)all_valid_positions.size() * all_valid_positions.size());
    std::cout << "todo: " << todo << "\n";
    int done = 0;
    for (const auto& cheat_start : all_valid_positions)
      for (const auto& cheat_end : all_valid_positions) {
        [&]() {
          if (cheat_start == cheat_end) return;
          const int cheat_steps = cheat_start.ManhattanDistance(cheat_end);
          if (cheat_steps > 20) return;
          const int steps = Bfs(cheat_start, cheat_end) + cheat_steps - 1;
          if (steps == 1) std::cout << cheat_start << " " << cheat_end << "\n";
          count_by_steps[steps]++;
        }();
        if (++done % 1000000 == 0) {
          std::cout << "done: " << ((float)done / todo) << "\n";
          std::fflush(stdout);
        }
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
    visited.resize(
        n, std::vector<std::vector<bool>>(m, std::vector<bool>(2, false)));
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

    fastest_path = Bfs(kNil, kNil);
    std::cout << "fastest_path: " << fastest_path << "\n";

    std::map<int, int> count_by_steps = TryAllCheats();

    int ans = 0;
    for (const auto& [steps, count] : count_by_steps) {
      const int saved = fastest_path - steps;
      // if (saved == 0) continue;
      if (saved < minimum_saved) continue;
      std::cout << "cheats: " << count << " | saved: " << saved << "\n";
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
