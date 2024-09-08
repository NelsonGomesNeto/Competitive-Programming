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

const int maxN = 1 << 18; int n, m;
int a[maxN];
bool has[maxN + 1];

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    dsu = DSU(n);

    memset(has, false, sizeof(has));
    for (int i = 0; i < m; i++)
    {
      scanf("%d", &a[i]);
      has[a[i]] = true;
    }

    vector<pair<int, int>> ans;
    
    // Surprisingly: this is O(n*ackermanInv) ~ O(n*lg)
    for (int x = 1; x < n; x++)
      if (!has[x] && !dsu.sameSet(0, x))
        for (int u = 0; u < n; u++)
        {
          int v = u ^ x;
          // u ^ v = u ^ (u ^ x) = x, which is not in A
          if (!dsu.sameSet(u, v)) ans.push_back({u, v});
          dsu.merge(u, v);
        }

    if (dsu.setSize(0) == n)
    {
      for (auto &[u, v]: ans)
        printf("%d %d\n", u, v);
    }
    else
      printf("-1\n");
  }
  return 0;
}