#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

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
DSU dsu;

int GetCompressedIndex(const std::vector<int>& a, const int x) {
  return std::lower_bound(a.begin(), a.end(), x) - a.begin();
}

struct TestCase {
  int n, m;
  std::vector<std::pair<int, int>> edges;
  std::vector<std::vector<std::pair<int, int>>> graph;
  DSU dsu;

  int GetNextDisconnectedComponent(const int r,
                                   std::unordered_set<int>& disconnected) {
    int to_remove = -1;
    for (const auto& c : disconnected) {
      if (dsu.SameSet(r, c)) continue;
      to_remove = c;
      break;
    }
    assert(to_remove != -1);
    disconnected.erase(to_remove);
    dsu.Merge(r, to_remove);
    return to_remove;
  }

  bool Run() {
    if (!(std::cin >> n >> m)) return false;
    edges.resize(m);
    graph.resize(n, std::vector<std::pair<int, int>>{});
    for (int i = 0; i < m; ++i) {
      auto& [u, v] = edges[i];
      std::cin >> u >> v;
      --u, --v;
      graph[u].emplace_back(v, i);
      if (u != v) graph[v].emplace_back(u, i);
    }

    dsu = DSU(n);
    for (const auto& [u, v] : edges) {
      dsu.Merge(u, v);
    }

    std::unordered_map<int, std::vector<int>> components;
    for (int i = 0; i < n; ++i) {
      components[dsu.Root(i)].push_back(i);
    }
    std::unordered_set<int> disconnected;
    for (const auto& [r, _] : components) disconnected.insert(r);

    std::vector<std::tuple<int, int, int>> ans;
    for (auto& [r, childs] : components) {
      if (disconnected.size() == 1) break;

      std::sort(childs.begin(), childs.end());
      int total_edges = 0;
      for (const auto& c : childs) {
        for (const auto& [v, _] : graph[c]) total_edges += c <= v;
      }
      if (total_edges + 1 < childs.size()) continue;
      DEBUG std::cout << r << " | " << (int)childs.size() << " | "
                      << total_edges << "\n";

      DSU internal(childs.size());
      std::vector<std::pair<int, int>> wasteful_edges;
      for (const auto& c : childs) {
        for (const auto& [v, ei] : graph[c]) {
          if (c > v) continue;
          const int ci = GetCompressedIndex(childs, c);
          const int vi = GetCompressedIndex(childs, v);
          if (internal.SameSet(ci, vi)) {
            wasteful_edges.emplace_back(ei, c);
          } else {
            internal.Merge(ci, vi);
          }
        }
      }
      for (const auto& [ei, u] : wasteful_edges) {
        if (disconnected.size() == 1) break;
        ans.emplace_back(ei, u, GetNextDisconnectedComponent(r, disconnected));
      }
    }

    std::cout << ans.size() << "\n";
    for (const auto& [i, u, w] : ans) {
      std::cout << (i + 1) << " " << (u + 1) << " " << (w + 1) << "\n";
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
