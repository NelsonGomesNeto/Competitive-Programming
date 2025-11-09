#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const char kStart = 'S', kEnd = 'E';
const int kRotationScore = 1000, kMoveScore = 1;
const int kInfinity = 1e9;

enum class Direction { kUp, kRight, kDown, kLeft };
std::ostream& operator<<(std::ostream& out, const Direction& d) {
  return out << (int)d;
}
const std::vector<Direction> kAllDirections{Direction::kUp, Direction::kRight,
                                            Direction::kDown, Direction::kLeft};
const std::string kDirectionAscii = "^>v<";
Direction Turn(const Direction dir, const bool clockwise) {
  const int nxt_dir =
      (((int)dir) + (clockwise ? 1 : 3)) % (int)kAllDirections.size();
  return (Direction)nxt_dir;
}

struct Vec {
  int i, j;

  Vec Add(const Vec& other) const { return Vec{i + other.i, j + other.j}; }
  bool operator==(const Vec& other) const {
    return i == other.i && j == other.j;
  }
  bool operator<(const Vec& other) const {
    return i < other.i || (i == other.i && j < other.j);
  }
  friend std::ostream& operator<<(std::ostream& out, const Vec& v) {
    return out << "(" << v.i << ", " << v.j << ")";
  }
};
const std::vector<Vec> kDirectionToVector{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
bool Valid(const int x, const int limit) { return x >= 0 && x < limit; }

struct Problem {
  int n, m;
  std::vector<std::string> map, filled_map;
  Vec start_pos, end_pos;
  Direction start_dir = Direction::kRight;
  std::vector<std::vector<std::vector<int>>> memo;
  std::map<std::pair<Vec, Direction>, std::pair<Vec, Direction>> prv;

  struct State {
    Vec pos;
    Direction dir;
    int score;
    bool operator<(const State& other) const { return score > other.score; }
  };
  int FindBestPath() {
    for (auto& line : memo)
      for (auto& col : line) std::ranges::fill(col, kInfinity);
    prv.clear();

    std::priority_queue<State> pq;
    pq.emplace(start_pos, kAllDirections[(int)start_dir], 0);
    memo[start_pos.i][start_pos.j][(int)start_dir] = 0;
    int ans = kInfinity;
    while (!pq.empty()) {
      const auto [pos, dir, score] = pq.top();
      pq.pop();

      // std::cout << pos << " " << dir << " " << score << "\n";
      // std::fflush(stdout);

      if (score > memo[pos.i][pos.j][(int)dir]) continue;

      if (pos == end_pos) {
        // return score;
        ans = std::min(ans, score);
        continue;
      }

      auto AddNext = [&](const Vec nxt_pos, const Direction nxt_dir,
                         const int nxt_score) {
        if (!Valid(nxt_pos.i, n) || !Valid(nxt_pos.j, m) ||
            map[nxt_pos.i][nxt_pos.j] == '#')
          return;
        auto& nxt_memo = memo[nxt_pos.i][nxt_pos.j][(int)nxt_dir];
        if (nxt_score >= nxt_memo) return;
        nxt_memo = nxt_score;
        prv[std::make_pair(nxt_pos, nxt_dir)] = std::make_pair(pos, dir);
        pq.emplace(nxt_pos, nxt_dir, nxt_score);
      };

      AddNext(pos, Turn(dir, /*clockwise=*/false), score + kRotationScore);
      AddNext(pos, Turn(dir, /*clockwise=*/true), score + kRotationScore);
      AddNext(pos.Add(kDirectionToVector[(int)dir]), dir, score + kMoveScore);
    }
    return ans;
  }

  void PrintBestPath() {
    filled_map = map;
    std::pair<Vec, Direction> curr = {end_pos, Direction::kRight};
    int lol = 0;
    while (curr.first != start_pos || curr.second != start_dir) {
      if (filled_map[curr.first.i][curr.first.j] == '.')
        filled_map[curr.first.i][curr.first.j] =
            kDirectionAscii[(int)curr.second];
      const auto it = prv.find(curr);
      if (it == prv.end()) {
        std::cout << "\tmiou tudo\n";
        break;
      }
      if (curr.first == it->second.first)
        lol += 1000;
      else
        lol += 1;
      curr = it->second;
    }

    for (const auto& line : filled_map) std::cout << line << "\n";
    std::cout << "\t" << lol << "\n";
  }

  void Rotate(std::vector<std::string>& mat) {
    std::vector<std::string> new_mat(mat[0].size(),
                                     std::string(mat.size(), '.'));
    for (int i = 0; i < mat.size(); ++i)
      for (int j = 0; j < mat[i].size(); ++j)
        new_mat[j][(int)mat.size() - 1 - i] = mat[i][j];
    mat = new_mat;
  }

  void Solve() {
    for (std::string line; std::getline(std::cin, line) && !line.empty();) {
      map.push_back(line);
    }
    // for (int k = 0; k < 2; ++k) Rotate(map);
    // start_dir = Direction::kLeft;

    n = map.size(), m = map[0].size();
    memo.resize(n, std::vector<std::vector<int>>(
                       m, std::vector<int>(kAllDirections.size(), false)));

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (map[i][j] == kStart) start_pos = Vec{i, j};
        if (map[i][j] == kEnd) end_pos = Vec{i, j};
      }
    }

    const int ans = FindBestPath();
    PrintBestPath();

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
