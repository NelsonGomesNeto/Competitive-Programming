#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
struct Edge { int from, to; lli c; };
vector<Edge> tree[maxN];
lli d[maxN];

lli maxPathBelow[maxN];
lli dfs(int u = 0, int prv = -1)
{
  maxPathBelow[u] = 0;
  for (auto &[uu, v, c]: tree[u])
    if (v != prv)
      maxPathBelow[u] = max(maxPathBelow[u], dfs(v, u) + c);
  return max(maxPathBelow[u], d[u]);
}
lli ans[maxN];
void dfs2(int u = 0, int prv = -1, lli curr = 0)
{
  vector<pair<lli, int>> bestPaths;
  for (auto &[uu, v, c]: tree[u])
    if (v != prv)
      bestPaths.emplace_back(c + max(d[v], maxPathBelow[v]), v);
  sort(bestPaths.begin(), bestPaths.end());

  for (auto &[uu, v, c]: tree[u])
    if (v != prv)
    {
      lli bestOtherPath = 0;
      if (bestPaths.size() >= 2 && bestPaths[bestPaths.size() - 2].second != v)
        bestOtherPath = bestPaths[bestPaths.size() - 2].first;
      if (bestPaths.back().second != v) bestOtherPath = bestPaths.back().first;

      DEBUG printf("\t%d %d - %lld - %lld %lld\n", u, v, maxPathBelow[v], curr, bestOtherPath);
      lli above = max(c + max(bestOtherPath, d[u]), c + curr);
      ans[v] = max(ans[v], above);
      dfs2(v, u, above);
    }
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++) tree[i].clear();
    for (int i = 1; i < n; i++)
    {
      Edge e; scanf("%d %d %lld", &e.from, &e.to, &e.c); e.from--, e.to--;
      tree[e.from].push_back(e);
      swap(e.from, e.to);
      tree[e.from].push_back(e);
    }
    for (int i = 0; i < n; i++) scanf("%lld", &d[i]);

    dfs();
    for (int i = 0; i < n; i++) ans[i] = maxPathBelow[i];
    dfs2();
    for (int i = 0; i < n; i++)
      printf("%lld\n", ans[i]);
  }
  return 0;
}