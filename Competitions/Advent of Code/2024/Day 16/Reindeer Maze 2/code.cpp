#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

/*
This problem was the first day I felt a bit lost hahaha.
I spent 2 hours on a stupid bug on `Turn` function in the very first part hahaha

I still don't have a great algorithm for k-th shortest path.

First solution:
It was running in 15s because I was literally storing the entire path and
running Dijkstra until it starts to find solutions with bigger distance.

Best solution:
20ms by maitaining a list of previous vertices like this:
  prv[i][j][dir] -> {{nxt_pos_k, nxt_dir_k}, ...} for all next positions that
  have best distance.
That way, we only need to find the shortest path with Dijkstra and later
traverse the optimal paths on `prv` graph.
And the complexity is equal to Dijkstra \o/.
*/

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
const std::vector<std::vector<Direction>> kDirectionTurnMap{
    {Direction::kLeft, Direction::kRight},
    {Direction::kUp, Direction::kDown},
    {Direction::kRight, Direction::kLeft},
    {Direction::kDown, Direction::kUp}};
Direction TurnOld(const Direction dir, const bool clockwise) {
  const int nxt_dir =
      (((int)dir) + (clockwise ? 1 : 3)) % (int)kAllDirections.size();
  return (Direction)nxt_dir;
}
Direction Turn(const Direction dir, const bool clockwise) {
  return kDirectionTurnMap[(int)dir][clockwise];
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

using vec_dir = std::pair<Vec, Direction>;
using vec_dir_list = std::vector<vec_dir>;

struct Problem {
  int n, m;
  std::vector<std::string> map, filled_map;
  Vec start_pos, end_pos;
  Direction start_dir = Direction::kRight;
  std::vector<std::vector<std::vector<int>>> memo;
  std::vector<std::vector<std::vector<vec_dir_list>>> prv;

  struct State {
    Vec pos;
    Direction dir;
    int score;
    bool operator<(const State& other) const { return score > other.score; }
  };
  int FindBestPaths() {
    for (auto& line : memo)
      for (auto& col : line) std::ranges::fill(col, kInfinity);
    for (auto& as : prv)
      for (auto& bs : as)
        for (auto& cs : bs) cs.clear();
    filled_map = map;

    std::priority_queue<State> pq;
    pq.emplace(start_pos, kAllDirections[(int)start_dir],
               memo[start_pos.i][start_pos.j][(int)start_dir] = 0);
    int best_path_score = kInfinity;
    while (!pq.empty()) {
      auto [pos, dir, score] = pq.top();
      pq.pop();

      if (score > memo[pos.i][pos.j][(int)dir]) continue;

      if (pos == end_pos) {
        best_path_score = score;
        break;
      }

      auto AddNext = [&](const Vec nxt_pos, const Direction nxt_dir,
                         const int nxt_score) {
        if (!Valid(nxt_pos.i, n) || !Valid(nxt_pos.j, m) ||
            map[nxt_pos.i][nxt_pos.j] == '#')
          return;
        auto& nxt_memo = memo[nxt_pos.i][nxt_pos.j][(int)nxt_dir];
        if (nxt_score > nxt_memo) return;

        // Maintain all prvs that have the same score.
        auto& prv_list = prv[nxt_pos.i][nxt_pos.j][(int)nxt_dir];
        if (nxt_score < nxt_memo) prv_list.clear();
        prv_list.emplace_back(pos, dir);

        // No need to explore the same state if the score isn't better.
        if (nxt_score >= nxt_memo) return;
        pq.emplace(nxt_pos, nxt_dir, nxt_memo = nxt_score);
      };

      AddNext(pos, Turn(dir, /*clockwise=*/false), score + kRotationScore);
      AddNext(pos, Turn(dir, /*clockwise=*/true), score + kRotationScore);
      AddNext(pos.Add(kDirectionToVector[(int)dir]), dir, score + kMoveScore);
    }

    // Find all paths with the same score.
    std::set<std::pair<Vec, Direction>> visited;
    std::queue<std::pair<Vec, Direction>> q;
    for (const Direction d : kAllDirections) {
      if (memo[end_pos.i][end_pos.j][(int)d] > best_path_score) continue;
      q.emplace(end_pos, d);
    }
    while (!q.empty()) {
      const auto ud = q.front();
      q.pop();
      const auto [u, d] = ud;

      const auto& prv_list = prv[u.i][u.j][(int)d];
      if (prv_list.empty()) break;
      if (visited.count(ud)) continue;
      visited.insert(ud);

      filled_map[u.i][u.j] = 'O';

      for (const auto nxt : prv_list) {
        q.push(nxt);
      }
    }
    std::cout << "best_path: " << best_path_score << "\n";

    int ans = 0;
    for (const auto& line : filled_map)
      for (const char c : line) ans += c == 'O' || c == 'S' || c == 'E';
    return ans;
  }

  void PrintBestPath() {
    for (const auto& line : filled_map) std::cout << line << "\n";
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
    prv.resize(n, std::vector<std::vector<vec_dir_list>>(
                      m, std::vector<vec_dir_list>(kAllDirections.size(),
                                                   vec_dir_list{})));

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (map[i][j] == kStart) start_pos = Vec{i, j};
        if (map[i][j] == kEnd) end_pos = Vec{i, j};
      }
    }

    const int ans = FindBestPaths();
    PrintBestPath();

    std::println("ans: {}", ans);
  }
};
Problem problem;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  for (const Direction d : kAllDirections) {
    for (int i = 0; i < 2; ++i) {
      assert(kDirectionTurnMap[(int)d][i] == TurnOld(d, i));
    }
  }
  problem.Solve();

  return 0;
}
