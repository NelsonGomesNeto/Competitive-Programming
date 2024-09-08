#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct DSU
{
  int size;
  vector<int> parents;
  DSU() { parents.clear(); }
  DSU(int sz) : size(sz) { init(); }
  void init() { parents.resize(size, -1); }
  int root(int u) { return parents[u] < 0 ? u : parents[u] = root(parents[u]); }
  void merge(int u, int v)
  {
    u = root(u), v = root(v);
    if (u == v) return;
    if (parents[u] > parents[v]) swap(u, v);
    parents[u] += parents[v];
    parents[v] = u;
  }
  int setSize(int u) { return -parents[root(u)]; }
  bool sameSet(int u, int v) { return root(u) == root(v); }
};
DSU dsu;

const int maxN = 2e5; int n, m;
vector<int> graph[maxN];
int ans[maxN];

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; i++) graph[i].clear();

    for (int i = 0; i < m; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      if (u > v) swap(u, v);
      graph[u].push_back(v);
    }

    dsu = DSU(n);
    int sets = 0;
    for (int i = n - 1; i >= 0; i--)
    {
      ans[i] = sets;
      sets++;
      for (int v: graph[i])
        if (!dsu.sameSet(i, v))
          sets--, dsu.merge(i, v);
    }

    for (int i = 0; i < n; i++)
      printf("%d\n", ans[i]);
  }
  return 0;
}