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
struct Edge
{
  int u, v; lli c;
  void read() { scanf("%d %d %lld", &u, &v, &c); u--, v--; }
  bool operator<(const Edge &other) const { return c < other.c; }
};
Edge edges[maxN];

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    dsu = DSU(n);
    lli total = 0;
    for (int i = 0; i < m; i++)
    {
      edges[i].read();
      total += edges[i].c;
    }

    sort(edges, edges+m);

    for (int i = 0; i < m; i++)
      if (!dsu.sameSet(edges[i].u, edges[i].v) || edges[i].c < 0)
      {
        total -= edges[i].c;
        dsu.merge(edges[i].u, edges[i].v);
      }
    printf("%lld\n", total);
  }
  return 0;
}