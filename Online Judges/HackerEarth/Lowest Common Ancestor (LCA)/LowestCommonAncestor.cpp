#include <bits/stdc++.h>
#define DEBUG if(0)

struct LCA {
  std::vector<std::vector<int>> tree;
  std::vector<int> level, log_memo;
  std::vector<std::vector<int>> ancestor;
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
  }

  void PrintMatrix() {
    // std::println("\tancestor:");
    // std::println("u\\a|{}", std::views::iota(0, log_n) |
    //                             std::views::transform([](const int a) {
    //                               return std::format("{:3d}", a);
    //                             }) |
    //                             std::views::join_with('|') |
    //                             std::ranges::to<std::string>());
    // for (int i = 0; i < n; ++i) {
    //   std::println("{:3d}|{}", i,
    //                ancestor[i] | std::views::transform([](const int a) {
    //                  return std::format("{:3d}", a);
    //                }) | std::views::join_with('|') |
    //                    std::ranges::to<std::string>());
    // }
  }

  void AddEdge(const int u, const int v) {
    tree[u].push_back(v), tree[v].push_back(u);
  }

  void Dfs(const int u, const int prv = -1) {
    // DEBUG { std::println("{}{:3d}", std::string(level[u] * 3, ' '), u); }
    for (const int v : tree[u]) {
      if (v == prv) continue;
      level[v] = level[u] + 1, ancestor[v][0] = u;
      Dfs(v, u);
    }
  }
  void Build() {
    level[0] = ancestor[0][0] = 0;
    Dfs(0);
    for (int i = 1; i < log_n; ++i) {
      for (int u = 0; u < n; ++u) {
        ancestor[u][i] = ancestor[ancestor[u][i - 1]][i - 1];
        // If you want to add something about the path, like weight:
        // weight[u][i] = combination of weight[u][i - 1] and
        // weight[ancestor[u][i - 1]][i - 1]
      }
    }
  }
  int Lca(int u, int v) {
    if (level[v] > level[u]) std::swap(u, v);

    // DEBUG {
    //   std::println("\tlevel diff: ({} - {}) = {} {:b}", level[u], level[v],
    //                level[u] - level[v], level[u] - level[v]);
    // }
    for (int diff = level[u] - level[v], i = 0; diff; diff >>= 1, ++i) {
      if (diff & 1) u = ancestor[u][i];
    }

    if (u == v) return u;

    // (i = log_n - 1; i >= 0; i --) works as well
    for (int i = log_memo[level[u] - 1]; ancestor[u][0] != ancestor[v][0];
         --i) {
      if (ancestor[u][i] != ancestor[v][i])
        u = ancestor[u][i], v = ancestor[v][i];
    }

    return ancestor[u][0];
  }
};
LCA lca;

int main() {
  int n;
  std::cin >> n;
  lca = LCA(n);
  for (int u = 1; u < n; ++u) {
    int parent;
    std::cin >> parent;
    lca.AddEdge(u, parent);
  }
  lca.Build();

  int q;
  std::cin >> q;
  int u;
  std::cin >> u;
  for (int qi = 1; qi < q; ++qi) {
    int v;
    std::cin >> v;
    u = lca.Lca(u, v);
  }
  // std::println("{}", u);
  std::cout << u << "\n";

  return 0;
}
