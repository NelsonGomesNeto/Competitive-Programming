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
};
const std::vector<Vec> kDirections = {Vec{-1, 0}, Vec{0, 1}, Vec{1, 0},
                                      Vec{0, -1}};

struct Problem {
  int n, m, k;
  std::vector<std::string> map;
  std::vector<Vec> bytes;
  Vec start_pos{0, 0}, end_pos;
  std::vector<std::vector<bool>> visited;

  bool Valid(const int x, const int limit) { return x >= 0 && x < limit; }
  bool Valid(const Vec& pos) {
    return Valid(pos.i, n) && Valid(pos.j, m) && map[pos.i][pos.j] == '.';
  }

  int FindShortestPath() {
    for (auto& line : visited) std::ranges::fill(line, false);

    std::queue<std::pair<Vec, int>> q;
    q.emplace(start_pos, 0);
    while (!q.empty()) {
      const auto [curr, steps] = q.front();
      q.pop();

      if (visited[curr.i][curr.j]) continue;
      visited[curr.i][curr.j] = true;

      if (curr == end_pos) {
        return steps;
      }

      for (const auto& d : kDirections) {
        const Vec nxt = curr.Add(d);
        if (!Valid(nxt)) continue;
        q.emplace(nxt, steps + 1);
      }
    }
    return -1;
  }

  Vec FindFirstBlocker() {
    for (const auto& ij : bytes) {
      const auto [i, j] = ij;
      map[i][j] = '#';
      const int shortest_path = FindShortestPath();
      if (shortest_path == -1) return ij;
    }
    return Vec{-1, -1};
  }

  void Solve() {
    std::cin >> n >> k;
    m = n;
    map.resize(n, std::string(m, '.'));
    visited.resize(n, std::vector<bool>(m, false));
    end_pos = Vec{n - 1, m - 1};

    for (int a, b; std::cin >> a;) {
      std::cin.ignore(1);
      std::cin >> b;
      bytes.emplace_back(b, a);
    }

    std::cout << n << "x" << n << " | first " << k << " bytes\n";
    for (const auto [i, j] : bytes) std::cout << i << " " << j << "\n";

    const Vec first_blocker = FindFirstBlocker();
    for (const auto& line : map) std::cout << line << "\n";

    const int ans = FindShortestPath();
    std::cout << "first_blocker: " << first_blocker.j << "," << first_blocker.i << "\n";
  }
};
Problem problem;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  problem.Solve();

  return 0;
}
