#include <bits/stdc++.h>
#define DEBUG if (0)

/*
This Eulerian Tour transforms a tree into a flat array which can be used to do
queries and updates on the subtree (using a Segment Tree for example).
*/

struct EulerianTour {
  const std::vector<std::vector<int>>& tree;
  EulerianTour(const std::vector<std::vector<int>>& tree_, const int root = 0)
      : tree(tree_) {
    first.resize(tree.size()), last.resize(tree.size());
    Build(root);
  }
  std::vector<int> tour;
  std::vector<int> first, last;
  void Build(const int u, const int prv = -1, const int depth = 0) {
    DEBUG std::println("{}{}", std::string(depth, ' '), u);
    first[u] = tour.size();
    tour.push_back(u);
    for (const int v : tree[u]) {
      if (v == prv) continue;
      Build(v, u, depth + 1);
      tour.push_back(u);
    }
    last[u] = (int)tour.size() - 1;
  }
};

int main() {
  int n;
  std::cin >> n;
  std::vector<std::vector<int>> tree(n, std::vector<int>{});
  for (int i = 1; i < n; ++i) {
    int u, v;
    std::cin >> u >> v;
    tree[u].push_back(v), tree[v].push_back(u);
  }

  EulerianTour et(tree);

  std::println("EulerTour: {}", et.tour);
  std::println("first: {}", et.first);
  std::println("last: {}", et.last);

  return 0;
}
