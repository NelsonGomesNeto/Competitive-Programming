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

int main()
{
  int n, q;
  while (scanf("%d %d", &n, &q) != EOF)
  {
    dsu = DSU(n);
    for (int i = 0; i < q; i++)
    {
      char op; scanf(" %c", &op);
      if (op == 'U')
      {
        int u, v; scanf("%d %d", &u, &v); u--, v--;
        dsu.merge(u, v);
        printf("Merged %d, %d\n", u + 1, v + 1);
      }
      else if (op == 'S')
      {
        int u; scanf("%d", &u); u--;
        printf("%d setSize: %d\n", u + 1, dsu.setSize(u));
      }
      else
      {
        int u, v; scanf("%d %d", &u, &v); u--, v--;
        printf("sameSet(%d, %d): %d\n", u + 1, v + 1, dsu.sameSet(u, v));
      }
    }
  }
  return 0;
}