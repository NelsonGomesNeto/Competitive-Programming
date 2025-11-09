#include <bits/stdc++.h>
#define DEBUG if (1)
#define lli long long int
#define ldouble long double

const int kDirections = 4;
const int kDi[4] = {-1, 0, 1, 0};
const int kDj[4] = {0, 1, 0, -1};
int GetDir(const char d) {
  switch (d) {
    case '^':
      return 0;
    case '>':
      return 1;
    case 'v':
      return 2;
    case '<':
    default:
      return 3;
  }
}

struct Problem {
  int n, m;
  std::vector<std::string> map;
  std::string movements;

  bool Valid(const int x, const int limit) { return x >= 0 && x < limit; }

  void TryMoveRobot(const int d, int& ri, int& rj) {
    const int ni = ri + kDi[d], nj = rj + kDj[d];

    int fi = ni, fj = nj;
    while (Valid(fi, n) && Valid(fj, m) && map[fi][fj] == 'O')
      fi += kDi[d], fj += kDj[d];

    if (!Valid(fi, n) || !Valid(fj, m) || map[fi][fj] == '#') return;

    map[ri][rj] = '.', map[ni][nj] = '@';
    if (fi != ni || fj != nj) map[fi][fj] = 'O';
    ri = ni, rj = nj;
  }

  void RunAllMovements() {
    auto [i, j] = [&]() {
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
          if (map[i][j] == '@') return std::make_pair(i, j);
        }
      assert(false);
      return std::make_pair(-1, -1);
    }();

    for (const char m : movements) {
      TryMoveRobot(GetDir(m), i, j);
    }
  }

  void Solve() {
    for (std::string line; std::getline(std::cin, line) && !line.empty();) {
      map.push_back(line);
    }
    n = map.size(), m = map[0].size();

    for (std::string line; std::getline(std::cin, line) && !line.empty();) {
      movements.append(line);
    }

    DEBUG {
      for (const auto& line : map) std::cout << line << "\n";
      std::cout << "\n";
      std::cout << movements << "\n";
      std::cout << "-----------\n";
    }

    RunAllMovements();

    DEBUG {
      for (const auto& line : map) std::cout << line << "\n";
      std::cout << "-----------\n";
    }

    int ans = 0;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        if (map[i][j] != 'O') continue;
        ans += 100 * i + j;
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
