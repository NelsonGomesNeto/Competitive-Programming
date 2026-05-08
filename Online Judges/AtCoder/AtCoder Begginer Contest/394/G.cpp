#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kDi[] = {-1, 0, 0, 1};
const int kDj[] = {0, -1, 1, 0};

struct DSU {
  int size;
  std::vector<int> parents;
  DSU() : size(0) { parents.clear(); }
  DSU(const int sz) : size(sz) { Init(); }
  void Init() { parents.resize(size, -1); }
  int Root(const int u) {
    return parents[u] < 0 ? u : parents[u] = Root(parents[u]);
  }
  void Merge(int u, int v) {
    u = Root(u), v = Root(v);
    if (u == v) return;
    if (parents[u] > parents[v]) std::swap(u, v);
    parents[u] += parents[v];
    parents[v] = u;
  }
  int SetSize(const int u) { return -parents[Root(u)]; }
  bool SameSet(const int u, const int v) { return Root(u) == Root(v); }
};

int ti, tj, th;
struct TestCase {
  int n, m;
  std::vector<std::vector<int>> f;
  int q;
  struct Query {
    int ui, uj, uh, vi, vj, vh, ans;
  };
  std::vector<Query> queries;
  std::vector<std::vector<std::vector<int>>> queries_by_pos;

  std::vector<std::tuple<int, int, int, int, int>> height_and_pos;
  std::vector<std::vector<std::vector<std::pair<int, int>>>> graph;
  int GetIndex(const int i, const int j) { return i * m + j; }

  DSU dsu;

  bool Run() {
    if (!(std::cin >> n >> m)) return false;

    f.resize(n, std::vector<int>(m));
    for (auto& fi : f)
      for (auto& fij : fi) std::cin >> fij;

    std::cin >> q;
    queries.resize(q);
    queries_by_pos.resize(n,
                          std::vector<std::vector<int>>(m, std::vector<int>{}));
    for (int i = 0; i < q; ++i) {
      auto& [ui, uj, uh, vi, vj, vh, ans] = queries[i];
      std::cin >> ui >> uj >> uh >> vi >> vj >> vh;
      --ui, --uj, --vi, --vj, ans = -1;
      queries_by_pos[ui][uj].push_back(i), queries_by_pos[vi][vj].push_back(i);
    }

    graph.resize(n, std::vector<std::vector<std::pair<int, int>>>(
                        m, std::vector<std::pair<int, int>>{}));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        for (int d = 0; d < 4; ++d) {
          const int ni = i + kDi[d], nj = j + kDj[d];
          if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
          graph[i][j].emplace_back(ni, nj);

          const auto ij = std::make_pair(i, j), ninj = std::make_pair(ni, nj);
          if (ij > ninj) continue;
          height_and_pos.emplace_back(std::min(f[i][j], f[ni][nj]), i, j, ni,
                                      nj);
        }
      }
    }
    std::sort(height_and_pos.begin(), height_and_pos.end());
    std::reverse(height_and_pos.begin(), height_and_pos.end());

    dsu = DSU(n * m);
    for (const auto& [minh, ui, uj, vi, vj] : height_and_pos) {
      dsu.Merge(GetIndex(ui, uj), GetIndex(vi, vj));
      // How do I find all queries that should be updated from this?
    }

    for (const auto& query : queries) {
      std::cout << query.ans << "\n";
    }

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

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
