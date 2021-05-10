#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n, m; lli x;
lli a[maxN];

struct DSU
{
  int size;
  vector<int> parents;
  vector<lli> c;
  DSU() { parents.clear(); }
  DSU(int sz) : size(sz) { init(); }
  void init()
  {
    parents.clear();
    parents.resize(size, -1);
    c.clear();
    c.resize(size, 0);
    for (int i = 0; i < size; i++) c[i] = a[i];
  }
  int root(int u)
  {
    return parents[u] < 0 ? u : parents[u] = root(parents[u]);
  }
  void merge(int u, int v)
  {
    u = root(u), v = root(v);
    if (u == v) return;
    if (parents[u] > parents[v]) swap(u, v);
    parents[u] += parents[v];
    c[u] += c[v] - x;
    parents[v] = u;
  }
  int setSize(int u) { return -parents[root(u)]; }
  lli getC(int u) { return c[root(u)]; }
  bool sameSet(int u, int v) { return root(u) == root(v); }
};
DSU dsu;

struct Edge
{
  int u, v, idx;
  lli getTotalC() const
  {
    return dsu.getC(u) + dsu.getC(v);
  }
  bool operator<(const Edge &other) const
  {
    return getTotalC() > other.getTotalC();
  }
};
Edge edges[maxN];

list<Edge> graph[maxN];

vector<int> prim()
{
  vector<int> ans;
  priority_queue<pair<lli, int>> pq;
  bool changes = false;
  do
  {
    changes = false;
    for (int i = 0; i < n; i++) pq.push({dsu.getC(i), i});

    while (!pq.empty())
    {
      int u = pq.top().second; lli prv = pq.top().first; pq.pop();
      lli myC = dsu.getC(u);

      for (auto it = graph[u].begin(); it != graph[u].end();)
      {
        if (dsu.sameSet(u, it->v))
          it = graph[u].erase(it);
        else if (myC + dsu.getC(it->v) >= x)
        {
          dsu.merge(u, it->v), ans.push_back(it->idx), changes = true;
          myC = dsu.getC(u);
          pq.push({myC, it->v});
          it = graph[u].erase(it);
        }
        else
          it++;
      }
    }
  } while (ans.size() < n - 1 && changes);
  return ans;
}

int main()
{
  while (~scanf("%d %d %lld", &n, &m, &x))
  {
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &a[i]);
      graph[i].clear();
    }
    for (int i = 0; i < m; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      graph[u].push_back(Edge{u, v, i});
      graph[v].push_back(Edge{v, u, i});
    }

    dsu = DSU(n);

    vector<int> ans = prim();

    if (ans.size() == n - 1)
    {
      printf("YES\n");
      for (int i = 0; i < ans.size(); i++)
        printf("%d\n", ans[i] + 1);
    }
    else
      printf("NO\n");
  }
  return 0;
}
