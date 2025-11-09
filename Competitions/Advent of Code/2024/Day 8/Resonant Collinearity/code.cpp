#include <bits/stdc++.h>
#define DEBUG if (1)
#define lli long long int
#define ldouble long double

const int kAlpha = 256;

struct Problem {
  int n, m;
  std::vector<std::string> map, filled_map;

  struct Pos {
    int i, j;
    int Dist(const Pos& other) const {
      return std::abs(i - other.i) + std::abs(j - other.j);
    }
    Pos Delta(const Pos& other) const { return {i - other.i, j - other.j}; }
    bool operator<(const Pos& other) const {
      return i < other.i || (i == other.i && j < other.j);
    }
  };
  std::vector<std::vector<Pos>> antennas_by_type;

  bool Valid(const Pos& pos) const {
    return pos.i >= 0 && pos.i < n && pos.j >= 0 && pos.j < m;
  }

  bool HasAntinode(const Pos& pos, const std::vector<Pos>& antennas) {
    std::set<Pos> deltas;
    for (const Pos& antenna : antennas) {
      deltas.insert(pos.Delta(antenna));
    }

    for (const Pos& delta : deltas) {
      if (delta.i == 0 && delta.j == 0) continue;
      const Pos double_delta = Pos{2 * delta.i, 2 * delta.j};
      if (deltas.count(double_delta)) return true;
    }
    return false;
  }

  void Solve() {
    for (std::string line; std::getline(std::cin, line) && !line.empty();)
      map.push_back(line);
    n = map.size(), m = map[0].size();
    filled_map = map;

    antennas_by_type.resize(kAlpha, {});
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        if (map[i][j] != '.') antennas_by_type[map[i][j]].emplace_back(i, j);
      }

    int ans = 0;
    std::vector<std::vector<bool>> done(n, std::vector<bool>(m, false));
    for (int ai = 0; ai < kAlpha; ++ai) {
      const std::vector<Pos>& antennas = antennas_by_type[ai];
      if (antennas.empty()) continue;

      for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
          const bool has = HasAntinode(Pos{i, j}, antennas);
          if (!has) continue;

          if (done[i][j]) continue;
          done[i][j] = true;

          ++ans;
          if (filled_map[i][j] == '.') filled_map[i][j] = '#';
        }
    }

    DEBUG {
      for (const auto& line : filled_map) std::cout << line << "\n";
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
