#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

/*
IIUC, I didn't have much time to play.
So I calculated that a brute force running a BFS for all cheat pairs (3M!) was
going to finish after running for a few minutes. 15 minutes later: I got my
answer and relaxed hahahah.

But the optimization isn't that hard to compute. Run 2 BFS to get the shortest
distance from `start_pos` to all other positions and similarly from `end_pos`.

Then, we go through all the cheat pairs and the distance using the cheat is
simply: dist_from_start[cheat_start] + dist_from_end[cheat_end] +
ManhattanDistance(cheat_start, cheat_end).
And this runs in 100ms O(|BFS| + n*m*max_cheat_dist^2) \o/.
*/

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
const int kMaxCheatSize = 20;

struct Problem {
  int n, m;
  int minimum_saved;
  std::vector<std::string> map;
  Vec start_pos, end_pos;

  bool Valid(const int x, const int limit) { return x >= 0 && x < limit; }
  bool Valid(const Vec& pos) {
    return Valid(pos.i, n) && Valid(pos.j, m) && map[pos.i][pos.j] != '#';
  }

  // Finds the shortest path to each position given a `start`.
  std::vector<std::vector<int>> Bfs(const Vec start) {
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
    std::vector<std::vector<int>> dist_from_start(n, std::vector<int>(m, kInf));

    std::queue<std::pair<Vec, int>> q;
    q.emplace(start, 0);
    while (!q.empty()) {
      const auto [pos, d] = q.front();
      q.pop();

      if (visited[pos.i][pos.j]) continue;
      visited[pos.i][pos.j] = true;
      dist_from_start[pos.i][pos.j] = d;

      for (const auto& dir : kDirections) {
        const Vec nxt_pos = pos.Add(dir);
        if (!Valid(nxt_pos) || visited[nxt_pos.i][nxt_pos.j]) continue;
        q.emplace(nxt_pos, d + 1);
      }
    }
    return dist_from_start;
  }

  std::map<int, int> TryAllCheats(
      const std::vector<std::vector<int>>& dist_from_start,
      const std::vector<std::vector<int>>& dist_from_end) {
    std::vector<Vec> all_valid_positions;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        if (map[i][j] != '#') all_valid_positions.emplace_back(i, j);

    std::cout << std::format("all_valid_positions: {}\n",
                             all_valid_positions.size());
    std::fflush(stdout);
    std::vector<std::pair<Vec, Vec>> cheat_pairs;
    for (const auto& cheat_start : all_valid_positions) {
      for (int di = -kMaxCheatSize; di <= kMaxCheatSize; ++di) {
        for (int dj = std::abs(di) - kMaxCheatSize,
                 end = kMaxCheatSize - std::abs(di);
             dj <= end; ++dj) {
          if (di == 0 && dj == 0) continue;
          const Vec cheat_end = cheat_start.Add(Vec{di, dj});
          if (!Valid(cheat_end)) continue;
          cheat_pairs.emplace_back(cheat_start, cheat_end);
        }
      }
    }

    const int todo = cheat_pairs.size();
    std::cout << std::format("todo: {}\n", todo);
    std::fflush(stdout);
    std::map<int, int> count_by_steps;
    int done = 0;
    for (const auto& [cheat_start, cheat_end] : cheat_pairs) {
      [&]() {
        assert(cheat_start != cheat_end);
        const int cheat_steps = cheat_start.ManhattanDistance(cheat_end);
        assert(cheat_steps <= kMaxCheatSize);
        const int steps = dist_from_start[cheat_start.i][cheat_start.j] +
                          dist_from_end[cheat_end.i][cheat_end.j] + cheat_steps;
        const int saved = count_by_steps[steps]++;
      }();
      if (++done % 100000 == 0) {
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

    const std::vector<std::vector<int>> dist_from_start = Bfs(start_pos);
    const std::vector<std::vector<int>> dist_from_end = Bfs(end_pos);
    const int original_path = dist_from_start[end_pos.i][end_pos.j];
    std::cout << "original_path: " << original_path << "\n";

    const std::map<int, int> count_by_steps =
        TryAllCheats(dist_from_start, dist_from_end);

    int ans = 0;
    for (const auto& [steps, count] : count_by_steps) {
      const int saved = original_path - steps;
      if (saved == 0) continue;
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
