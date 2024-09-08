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
DSU dsu, dsu2;

const int maxN = 1e3; int n, d;
int ans[maxN];
struct Edge
{
  int u, v;
  void read() { scanf("%d %d", &u, &v); u--, v--; }
};
Edge edges[maxN];

int main()
{
  int pundim = 0;
  while (~scanf("%d %d", &n, &d))
  {
    fill(ans, ans+n, 0);
    if (pundim++) printf("--------\n");

    dsu = DSU(n);
    dsu2 = DSU(n);
    for (int i = 0; i < d; i++)
    {
      edges[i].read();
      dsu2.merge(edges[i].u, edges[i].v);
    }

    int curr = 0;
    for (int i = 0; i < d; i++)
    {
      dsu = DSU(n), dsu2 = DSU(n);
      int good = 0;
      for (int j = 0; j <= i && j < d; j++)
      {
        int u = edges[j].u, v = edges[j].v;
        if (dsu.sameSet(u, v))
          good++;
        else
          dsu.merge(u, v), dsu2.merge(u, v);
      }

      DEBUG printf("\t%d %d - %d\n", edges[i].u, edges[i].v, good);

      int biggest = 0;
      for (int j = 0; j < n; j++)
        if (dsu.setSize(j) > dsu.setSize(biggest))
          biggest = j;
      for (int hehe = 0; hehe < good; hehe++)
      {
        int best = -1;
        for (int j = 0; j < n; j++)
          if (!dsu.sameSet(biggest, j) && (best == -1 || dsu.setSize(j) > dsu.setSize(best)))
            best = j;
        if (best == -1)
          for (int j = 0; j < n; j++)
            if (j != biggest)
              best = j;
        dsu.merge(biggest, best);
      }

      for (int j = 0; j < n; j++)
        ans[i] = max(ans[i], dsu.setSize(j) - 1);
    }

    for (int i = 0; i < d; i++)
      printf("%d\n", ans[i]);
  }
  return 0;
}
