#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n, m;
vector<int> graph[maxN];
int color[maxN];
bool dfs(int u = 0, int prv = -1)
{
  color[u] = prv == -1 ? 0 : (color[prv] + 1) % 4;
  for (int v: graph[u])
    if (color[v] == -1)
    {
      if (v != prv && !dfs(v, u))
        return false;
    }
    else if (color[v] == color[u])
      return false;
  return true;
}
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
  int t;
  while (~scanf("%d", &t))
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d %d", &n, &m);

      for (int i = 0; i < n; i++)
        graph[i].clear();
      dsu = DSU(n);
      for (int i = 0; i < m; i++)
      {
        int u, v; scanf("%d %d", &u, &v); u--, v--;
        dsu.merge(u, v);
        graph[u].push_back(v), graph[v].push_back(u);
      }
      memset(color, -1, sizeof(color));
      bool can = dfs();

      if (dsu.setSize(0) != n) printf("NO\n");
      else
      {
        vector<int> ans;
        for (int i = 0; i < n; i++)
          if (!(color[i] & 1))
            ans.push_back(i + 1);
        
        printf("YES\n%d\n", (int)ans.size());
        for (int i = 0; i < ans.size(); i++)
          printf("%d%c", ans[i], i < ans.size() - 1 ? ' ' : '\n');
      }
    }
  return 0;
}
