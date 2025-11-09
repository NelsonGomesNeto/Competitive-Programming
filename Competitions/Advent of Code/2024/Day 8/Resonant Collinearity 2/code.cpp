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
    Pos Add(const Pos& other) const { return {i + other.i, j + other.j}; }
    Pos Subtract(const Pos& other) const { return {i - other.i, j - other.j}; }
    bool operator<(const Pos& other) const {
      return i < other.i || (i == other.i && j < other.j);
    }

    friend std::ostream& operator<<(std::ostream& out, const Pos& p) {
      return out << "(" << p.i << ", " << p.j << ")";
    }
  };
  std::vector<std::vector<Pos>> antennas_by_type;

  bool Valid(const Pos& pos) const {
    return pos.i >= 0 && pos.i < n && pos.j >= 0 && pos.j < m;
  }

  bool HasAntinode(const Pos& pos, const std::vector<Pos>& antennas) {
    std::set<Pos> deltas;
    for (const Pos& antenna : antennas) {
      deltas.insert(pos.Subtract(antenna));
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
    auto Cnt = [&](const Pos& pos) {
      const int i = pos.i, j = pos.j;
      if (done[i][j]) return;

      ++ans;
      done[i][j] = true;
      if (filled_map[i][j] == '.') filled_map[i][j] = '#';
    };

    for (int ti = 0; ti < kAlpha; ++ti) {
      const std::vector<Pos>& antennas = antennas_by_type[ti];
      if (antennas.empty()) continue;

      for (int i = 0; i < antennas.size(); ++i) {
        const Pos& ai = antennas[i];
        for (int j = i + 1; j < antennas.size(); ++j) {
          const Pos& aj = antennas[j];
          const Pos delta = ai.Subtract(aj);
          if (delta.i == 0 && delta.j == 0) continue;

          Pos curr = ai;
          do {
            Cnt(curr);
            curr = curr.Add(delta);
          } while (Valid(curr));
          curr = ai.Subtract(delta);
          while (Valid(curr)) {
            Cnt(curr);
            curr = curr.Subtract(delta);
          }
        }
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
