#include <bits/stdc++.h>

/*
Finds the maximum matching with minimum cost.
Notice that you can multiple cost by -1 and it will find maximum cost instead.

Faster than MinCostFlow, but not as flexible.
If the capacity of a vertex is greater than 1, you will need to run Hungarian
multiple times. You probably will reduce the matrix each time, but if the
capacity is big (like 1000): Hungarian * 1000 probably won't pass :(.

How to use:
assigning `i` to `j` = `costs[i][j]`
So, in "flow" terms, the graph is like (vertex -[cost, flow]> vertex):
source (?) -[0, 1]> i (1 : n) -[cost[i][j], 1]> j (1 : n) -[0, 1]> sink (?)
*/

template <typename Cost>
struct Hungarian {
  int n;
  std::vector<std::vector<Cost>> costs;
  std::vector<Cost> u, v;
  std::vector<int> p, way;
  Cost inf;

  Hungarian() {}
  Hungarian(int n) : n(n), u(n + 1), v(n + 1), p(n + 1), way(n + 1) {
    inf = std::numeric_limits<Cost>::max();
    costs.resize(n, std::vector<Cost>(n, 0));
  }

  void AddEdge(int u, int v, Cost c) { costs[u][v] = c; }

  std::pair<Cost, std::vector<int>> Assignment() {
    for (int i = 1; i <= n; ++i) {
      p[0] = i;
      int j0 = 0;
      std::vector<Cost> minv(n + 1, inf);
      std::vector<int> used(n + 1, 0);
      do {
        used[j0] = true;
        int i0 = p[j0], j1 = -1;
        Cost delta = inf;
        for (int j = 1; j <= n; ++j) {
          if (used[j]) continue;
          Cost cur = costs[i0 - 1][j - 1] - u[i0] - v[j];
          if (cur < minv[j]) minv[j] = cur, way[j] = j0;
          if (minv[j] < delta) delta = minv[j], j1 = j;
        }
        for (int j = 0; j <= n; ++j) {
          if (used[j])
            u[p[j]] += delta, v[j] -= delta;
          else
            minv[j] -= delta;
        }
        j0 = j1;
      } while (p[j0] != 0);

      do {
        int j1 = way[j0];
        p[j0] = p[j1];
        j0 = j1;
      } while (j0);
    }
    std::vector<int> ans(n);
    for (int j = 1; j <= n; ++j) ans[p[j] - 1] = j - 1;
    return std::make_pair(-v[0], ans);
  }
};
Hungarian<int> hungarian;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  while (std::cin >> n) {
    hungarian = Hungarian<int>(n);

    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j) {
        int c;
        std::cin >> c;
        hungarian.AddEdge(i, j, c);
      }

    auto [min_cost, assignments] = hungarian.Assignment();
    std::cout << min_cost << "\n";
    std::cout << "Assignment:\n";
    for (int i = 0; i < n; ++i)
      std::cout << i << " - " << assignments[i] << "\n";
  }
}
