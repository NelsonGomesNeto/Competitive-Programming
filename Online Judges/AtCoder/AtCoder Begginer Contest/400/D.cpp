#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kInf = 1e9;
const int kDi[4] = {0, 1, -1, 0};
const int kDj[4] = {1, 0, 0, -1};

const bool IsValid(const int x, const int limit) { return x >= 0 && x < limit; }

struct TestCase {
  int n, m;
  struct Pos {
    int i, j;
    bool operator<(const Pos& other) const {
      return i < other.i || (i == other.i && j < other.j);
    }
    bool operator==(const Pos& other) const {
      return i == other.i && j == other.j;
    }
  };
  Pos start, end;
  std::vector<std::string> mat;

  bool Valid(const Pos& p) const { return IsValid(p.i, n) && IsValid(p.j, m); }

  struct State {
    Pos p;
    int dist, kicks;
    bool operator<(const State& other) const {
      return kicks > other.kicks || (kicks == other.kicks && dist > other.dist);
    }
  };
  std::vector<std::vector<std::pair<int, int>>> dist;
  int Dijkstra() {
    dist.resize(n, std::vector<std::pair<int, int>>(m, {kInf, kInf}));
    std::priority_queue<State> pq;
    pq.emplace(start, 0, 0);
    dist[start.i][start.j] = std::make_pair(0, 0);
    while (!pq.empty()) {
      State s = pq.top();
      pq.pop();

      if (s.p == end) return s.kicks;
      if (std::make_pair(s.kicks, s.dist) > dist[s.p.i][s.p.j]) continue;

      for (int d = 0; d < 4; ++d) {
        int ni = s.p.i + kDi[d], nj = s.p.j + kDj[d];
        if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
        if (mat[ni][nj] == '.') {
          auto new_dist = std::make_pair(s.kicks, s.dist + 1);
          if (new_dist >= dist[ni][nj]) continue;
          dist[ni][nj] = new_dist;
          pq.emplace(Pos{ni, nj}, s.dist + 1, s.kicks);
        } else {
          auto try_add = [&](const Pos newp, const int new_dist) {
            if (!Valid(newp)) return;
            auto hehe = std::make_pair(s.kicks + 1, new_dist);
            if (hehe >= dist[newp.i][newp.j]) return;
            dist[newp.i][newp.j] = hehe;
            pq.emplace(newp, new_dist, s.kicks + 1);
          };
          try_add(Pos{ni, nj}, s.dist + 1);
          try_add(Pos{ni + kDi[d], nj + kDj[d]}, s.dist + 2);
        }
      }
    }
    return -1;
  }

  bool Run() {
    if (!(std::cin >> n >> m)) return false;
    mat.resize(n);
    for (auto& line : mat) std::cin >> line;
    std::cin >> start.i >> start.j >> end.i >> end.j;
    --start.i, --start.j, --end.i, --end.j;

    int ans = Dijkstra();
    std::cout << ans << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);

  // int test_cases;
  // std::cin >> test_cases;
  // for (int t = 1; t <= test_cases; ++t) {
  //   test_case = TestCase{};
  //   test_case.Run();
  // }

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
