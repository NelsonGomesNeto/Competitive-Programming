#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50; int n;
lli c[maxN];
vector<int> tree[maxN];

int parent[maxN];
vector<int> leafs;
void dfs(int u = 0, int prv = -1)
{
  if (tree[u].size() == 1 && tree[u][0] == prv)
    leafs.push_back(u);
  for (int v: tree[u])
    if (v != prv)
      parent[v] = u, dfs(v, u);
}
lli climb(int u)
{
  lli total = c[0];
  while (u != 0)
  {
    if (c[u] == -1) return 0;
    total += c[u];
    u = parent[u];
  }
  return total;
}
void deleteOnPath(int u)
{
  c[0] = 0;
  while (u != 0)
  {
    c[u] = -1;
    u = parent[u];
  }
}


int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%lld", &c[i]);
    for (int i = 0; i < n; i++) tree[i].clear();
    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
    }

    leafs.clear();
    dfs();
    lli ans = 0;
    int bestLeaf = 0; lli best = 0;
    for (int i: leafs)
    {
      lli now = climb(i);
      if (now > best) best = now, bestLeaf = i;
    }
    ans += best;

    deleteOnPath(bestLeaf);

    bestLeaf = 0, best = 0;
    for (int i: leafs)
    {
      lli now = climb(i);
      if (now > best) best = now, bestLeaf = i;
    }
    ans += best;

    printf("Case #%d: %lld\n", tt, ans);
  }
  return 0;
}