#include <bits/stdc++.h>
#define DEBUG if (1)

// TODO: Use templates instead of `std::pair<int, int>` for the (node, weight).
// That should also allow it to define custom nil and merge functions for the
// values.
struct LCA {
  std::vector<std::vector<std::pair<int, int>>> tree;
  std::vector<int> level, log_memo;
  std::vector<std::vector<int>> ancestor;
  std::vector<std::vector<int>> weights;
  int n, log_n;
  LCA() {}
  LCA(const int n_) : n(n_), log_n(std::ceil(std::log2(std::max(2, n)))) {
    log_memo.clear();
    log_memo.resize(n + 1);
    log_memo[1] = 0;
    for (int i = 2; i <= n; ++i) log_memo[i] = log_memo[i >> 1] + 1;

    tree.clear();
    tree.resize(n);
    level.clear();
    level.resize(n, 0);
    ancestor.clear();
    ancestor.resize(n, std::vector<int>(log_n, 0));
    weights.clear();
    weights.resize(n, std::vector<int>(log_n, 0));
  }

  void PrintMatrix() {
    std::println("\tancestor table:");
    std::println("u\\a|{}", std::views::iota(0, log_n) |
                                std::views::transform([](const int a) {
                                  return std::format("{:3d}", a);
                                }) |
                                std::views::join_with('|') |
                                std::ranges::to<std::string>());
    for (int i = 0; i < n; ++i) {
      std::println("{:3d}|{}", i,
                   ancestor[i] | std::views::transform([](const int a) {
                     return std::format("{:3d}", a);
                   }) | std::views::join_with('|') |
                       std::ranges::to<std::string>());
    }
  }

  void AddEdge(const int u, const int v, const int cost) {
    tree[u].emplace_back(v, cost), tree[v].emplace_back(u, cost);
  }

  void Dfs(const int u, const int prv = -1) {
    DEBUG if (prv == -1) {
      std::println("{}{:3d}", std::string(level[u] * 3, ' '), u);
    }
    for (const auto [v, cost] : tree[u]) {
      if (v == prv) continue;
      level[v] = level[u] + 1, ancestor[v][0] = u, weights[v][0] = cost;
      DEBUG {
        std::println("{}{:3d},{}", std::string(level[v] * 3, ' '), v, cost);
      }
      Dfs(v, u);
    }
  }
  void Build() {
    level[0] = ancestor[0][0] = weights[0][0] = 0;
    DEBUG std::println("\ttree:");
    Dfs(0);
    for (int i = 1; i < log_n; ++i) {
      for (int u = 0; u < n; ++u) {
        ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
        weights[u][i] = weights[u][i - 1] + weights[ancestor[u][i - 1]][i - 1];
      }
    }
  }
  std::pair<int, int> Lca(int u, int v) {
    if (level[v] > level[u]) std::swap(u, v);

    int cost = 0;

    DEBUG {
      std::println("\tlevel diff: ({} - {}) = {} {:b}", level[u], level[v],
                   level[u] - level[v], level[u] - level[v]);
    }
    for (int diff = level[u] - level[v], i = 0; diff; diff >>= 1, ++i) {
      if (diff & 1) {
        cost += weights[u][i];
        u = ancestor[u][i];
      }
    }

    if (u == v) return {u, cost};

    // (i = log_n - 1; i >= 0; i --) works as well
    for (int i = log_memo[level[u] - 1]; ancestor[u][0] != ancestor[v][0];
         --i) {
      if (ancestor[u][i] != ancestor[v][i]) {
        cost += weights[u][i] + weights[v][i];
        u = ancestor[u][i], v = ancestor[v][i];
      }
    }

    cost += weights[u][0] + weights[v][0];
    return {ancestor[u][0], cost};
  }
};
LCA lca;

int main() {
  int n;
  std::cin >> n;
  lca = LCA(n);

  for (int i = 0; i < n - 1; ++i) {
    int u, v, cost;
    std::cin >> u >> v >> cost;
    lca.AddEdge(u, v, cost);
  }
  lca.Build();
  lca.PrintMatrix();

  int q;
  std::cin >> q;
  for (int qi = 0; qi < q; ++qi) {
    int u, v;
    if (!(std::cin >> u >> v)) break;
    const auto [a, cost] = lca.Lca(u, v);
    std::println("LCA({}, {}) = (a: {}, cost: {})", u, v, a, cost);
  }
  return (0);
}
