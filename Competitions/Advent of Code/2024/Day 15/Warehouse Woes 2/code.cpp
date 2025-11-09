#include <bits/stdc++.h>
#define DEBUG if (0)
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

std::vector<
    std::function<bool(const std::pair<int, int>&, const std::pair<int, int>&)>>
    kCompByDir{
        [](const std::pair<int, int>& a, const std::pair<int, int>& b) -> bool {
          return a.first < b.first;
        },
        [](const std::pair<int, int>& a, const std::pair<int, int>& b) -> bool {
          return a.second > b.second;
        },
        [](const std::pair<int, int>& a, const std::pair<int, int>& b) -> bool {
          return a.first > b.first;
        },
        [](const std::pair<int, int>& a, const std::pair<int, int>& b) -> bool {
          return a.second < b.second;
        }};

struct Problem {
  int n, m;
  std::vector<std::string> map;
  std::string movements;

  void PrintMap() {
    for (const auto& line : map) std::cout << line << "\n";
  }

  bool Valid(const int x, const int limit) { return x >= 0 && x < limit; }

  bool IsBox(const int i, const int j) {
    return map[i][j] == '[' || map[i][j] == ']';
  }
  bool NeighborIsEmptyOrBox(const int d, const int i, const int j) {
    const int ni = i + kDi[d], nj = j + kDj[d];
    if (!Valid(ni, n) || !Valid(nj, m) || map[ni][nj] == '#') return false;
    return true;
  }
  std::set<std::pair<int, int>> FindBoxesByDir(const int d, const int si,
                                               const int sj) {
    std::set<std::pair<int, int>> boxes;
    std::queue<std::pair<int, int>> q;
    q.emplace(si, sj);
    while (!q.empty()) {
      const auto ij = q.front();
      const auto [i, j] = ij;
      q.pop();

      if (!Valid(i, n) || !Valid(j, m) || !IsBox(i, j)) continue;
      if (boxes.count(ij)) continue;
      boxes.insert(ij);

      // Add rest of the box
      if (map[i][j] == ']') q.emplace(i, j - 1);
      if (map[i][j] == '[') q.emplace(i, j + 1);
      // Add neighbor
      q.emplace(i + kDi[d], j + kDj[d]);
    }
    return boxes;
  }
  void TryMoveRobot(const int d, int& ri, int& rj) {
    const int ni = ri + kDi[d], nj = rj + kDj[d];
    if (!Valid(ni, n) || !Valid(nj, m) || map[ni][nj] == '#') return;

    std::set<std::pair<int, int>> boxes = FindBoxesByDir(d, ni, nj);
    for (const auto& [bi, bj] : boxes) {
      if (!NeighborIsEmptyOrBox(d, bi, bj)) return;
    }

    std::vector<std::pair<int, int>> boxes_to_move(boxes.begin(), boxes.end());
    std::ranges::sort(boxes_to_move, kCompByDir[d]);
    for (const auto& bij : boxes_to_move) {
      const auto [bi, bj] = bij;
      const int bni = bi + kDi[d], bnj = bj + kDj[d];
      map[bni][bnj] = map[bi][bj];
      map[bi][bj] = '.';
    }

    map[ri][rj] = '.', map[ni][nj] = '@';
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
      DEBUG {
        std::cout << "Move " << m << ":\n";
        PrintMap();
        std::cout << "\n";
      }
    }
  }

  void Solve() {
    auto Expand = [&](const char c, std::string& target) {
      switch (c) {
        case '#':
          target.append("##");
          return;
        case 'O':
          target.append("[]");
          return;
        case '.':
          target.append("..");
          return;
        case '@':
        default:
          target.append("@.");
          return;
      }
    };
    for (std::string line; std::getline(std::cin, line) && !line.empty();) {
      auto& new_line = map.emplace_back();
      for (const char c : line) {
        Expand(c, new_line);
      }
    }
    n = map.size(), m = map[0].size();

    for (std::string line; std::getline(std::cin, line) && !line.empty();) {
      movements.append(line);
    }

    std::cout << "start:\n";
    PrintMap();
    std::cout << "\n";
    std::cout << movements << "\n";
    std::cout << "-----------\n";

    RunAllMovements();

    std::cout << "final:\n";
    PrintMap();
    std::cout << "-----------\n";

    int ans = 0;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        if (map[i][j] != '[') continue;
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
