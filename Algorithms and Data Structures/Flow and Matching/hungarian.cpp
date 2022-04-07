#include <bits/stdc++.h>
using namespace std;

/*
Finds the maximum matching with minimum cost.
Notice that you can multiple cost by -1 and it will find maximum cost instead.

Faster than MinCostFlow, but not as flexible.
If the capacity of a vertex is greater than 1, you will need to run Hungarian
multiple times. You probably will reduce the matrix each time, but if the
capacity is big (like 1000): Hungarian * 1000 probably won't pass :(.
*/

template<typename T>
struct Hungarian {
  int n;
  vector<vector<T>> costs;
  vector<T> u, v;
  vector<int> p, way;
  T inf;

  Hungarian() {}
  Hungarian(int n) : n(n), u(n+1), v(n+1), p(n+1), way(n+1)
  {
    inf = numeric_limits<T>::max();
    costs.resize(n, vector<T>(n, 0));
  }
  pair<T, vector<int>> assignment()
  {
    for (int i = 1; i <= n; i++) {
      p[0] = i;
      int j0 = 0;
      vector<T> minv(n+1, inf);
      vector<int> used(n+1, 0);
      do {
        used[j0] = true;
        int i0 = p[j0], j1 = -1;
        T delta = inf;
        for (int j = 1; j <= n; j++) if (!used[j]) {
          T cur = costs[i0-1][j-1] - u[i0] - v[j];
          if (cur < minv[j]) minv[j] = cur, way[j] = j0;
          if (minv[j] < delta) delta = minv[j], j1 = j;
        }
        for (int j = 0; j <= n; j++)
          if (used[j]) u[p[j]] += delta, v[j] -= delta;
          else minv[j] -= delta;
        j0 = j1;
      } while (p[j0] != 0);
      do {
        int j1 = way[j0];
        p[j0] = p[j1];
        j0 = j1;
      } while (j0);
    }
    vector<int> ans(n);
    for (int j = 1; j <= n; j++) ans[p[j]-1] = j-1;
    return make_pair(-v[0], ans);
  }
};
Hungarian<int> hungarian;

const int maxN = 5e3;
int costs[maxN][maxN];
int n;

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        scanf("%d", &costs[i][j]);

    hungarian = Hungarian<int>(n);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        hungarian.costs[i][j] = costs[i][j];

    auto ans = hungarian.assignment();
    printf("%d\n", ans.first);
    printf("Assignment:\n");
    for (int i = 0; i < n; ++i)
      printf("%d - %d\n", i, ans.second[i]);
  }
}