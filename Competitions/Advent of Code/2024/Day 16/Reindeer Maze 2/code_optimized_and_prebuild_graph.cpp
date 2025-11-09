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

using vec_dir_weight = std::tuple<Vec, Direction, int>;
using vec_dir_weight_list = std::vector<vec_dir_weight>;
using vec_dir = std::pair<Vec, Direction>;
using vec_dir_list = std::vector<vec_dir>;

struct Problem {
  int n, m;
  std::vector<std::string> map, filled_map;
  std::vector<std::vector<std::vector<vec_dir_weight_list>>> graph;
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

      for (const auto [nxt_pos, nxt_dir, weight] :
           graph[pos.i][pos.j][(int)dir]) {
        AddNext(nxt_pos, nxt_dir, score + weight);
      }
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

      if (filled_map[u.i][u.j] == '.') filled_map[u.i][u.j] = 'O';

      for (const auto nxt : prv_list) {
        q.push(nxt);
      }
    }
    filled_map[start_pos.i][start_pos.j] = 'O';
    filled_map[end_pos.i][end_pos.j] = 'O';
    std::cout << "best_path: " << best_path_score << "\n";

    int ans = 0;
    for (const auto& line : filled_map)
      for (const char c : line) ans += c == 'O';
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
    graph.resize(n, std::vector<std::vector<vec_dir_weight_list>>(
                        m, std::vector<vec_dir_weight_list>(
                               kAllDirections.size(), vec_dir_weight_list{})));

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (map[i][j] == kStart) start_pos = Vec{i, j};
        if (map[i][j] == kEnd) end_pos = Vec{i, j};
        if (map[i][j] == '#') continue;

        const Vec pos{i, j};
        for (const Direction dir : kAllDirections) {
          auto AddIfValid = [&](const Direction nxt_dir, const int weight) {
            const Vec nxt_pos = pos.Add(kDirectionToVector[(int)nxt_dir]);
            if (!Valid(nxt_pos.i, n) || !Valid(nxt_pos.j, m) ||
                map[nxt_pos.i][nxt_pos.j] == '#')
              return;
            graph[i][j][(int)dir].emplace_back(nxt_pos, nxt_dir, weight);
          };
          AddIfValid(dir, kMoveScore);
          AddIfValid(Turn(dir, /*clockwise=*/false),
                     kMoveScore + kRotationScore);
          AddIfValid(Turn(dir, /*clockwise=*/true),
                     kMoveScore + kRotationScore);
          AddIfValid(Turn(Turn(dir, /*clockwise=*/true), /*clockwise=*/true),
                     kMoveScore + 2 * kRotationScore);
        }
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
