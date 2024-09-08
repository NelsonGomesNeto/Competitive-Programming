#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
int n, q;
vector<vector<int>> g, gs;
int dad[maxN];
int ans[maxN];

void update(int u, int v)
{
  const int minuv = min(ans[u], ans[v]);
  ans[u] = ans[v] = minuv;
}

struct DSU
{
  int size;
  vector<int> parents;
  DSU() { parents.clear(); }
  DSU(int sz) : size(sz) { init(); }
  void init() { parents.resize(size, -1); }
  int root(int u)
  {
    return parents[u] < 0 ? u : parents[u] = root(parents[u]);
  }
  void merge(int u, int v)
  {
    u = root(u), v = root(v);
    if (u == v)
      return;
    if (parents[u] > parents[v])
      swap(u, v);
    update(u, v);
    parents[u] += parents[v];
    parents[v] = u;
  }
  int setSize(int u) { return -parents[root(u)]; }
  bool sameSet(int u, int v) { return root(u) == root(v); }
  int minOnSet(int u) { return ans[root(u)]; }
};
DSU dsu;

int precalc(int u)
{
  int& res = ans[u];
  if (res != -1) return res;
  res = u;
  for (const int v : g[u])
    res = min(res, precalc(v));
  return res;
}

void merge(int u, int target)
{
  while (!dsu.sameSet(u, target))
  {
    dsu.merge(u, dad[u]);
    int newU = dsu.minOnSet(u);
    u = newU;
  }
}

int main()
{
  int tt = 0;
  while (~scanf("%d", &n))
  {
    if (tt++) printf("---------------\n");

    dsu = DSU(n);

    g.clear();
    g.resize(n);
    for (int i = 1; i < n; ++i)
    {
      int u;
      scanf("%d", &u);
      --u;
      g[u].push_back(i);
      dad[i] = u;
    }

    memset(ans, -1, sizeof(ans));
    for (int i = 0; i < n; ++i)
      precalc(i);

    int q;
    scanf("%d", &q);
    while (q--)
    {
      int op;
      scanf("%d", &op);
      if (op == 1)
      {
        int u, v;
        scanf("%d %d", &u, &v);
        --u, --v;
        merge(u, v);
      }
      else
      {
        int u;
        scanf("%d", &u);
        --u;
        printf("%d\n", dsu.minOnSet(u) + 1);
      }
    }
  }
  return 0;
}
