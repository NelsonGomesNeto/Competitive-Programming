#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
vector<int> tree[maxN];

lli level[maxN], subtreeSize[maxN];
void dfs(int u = 0, int prv = -1)
{
  subtreeSize[u] = 1;
  for (int v: tree[u])
    if (v != prv)
    {
      level[v] = level[u] + 1;
      dfs(v, u);
      subtreeSize[u] += subtreeSize[v];
    }
}
lli levelSum[maxN];
void dfs2(int u = 0, int prv = -1)
{
  levelSum[u] = level[u];
  for (int v: tree[u])
    if (v != prv)
    {
      dfs2(v, u);
      levelSum[u] += levelSum[v];
    }
}
lli above[maxN];
void dfs3(lli up = 0, int u = 0, int prv = -1)
{
  DEBUG printf("\t\t%d %lld\n", u + 1, up);
  above[u] = up;
  for (int v: tree[u])
    if (v != prv)
    {
      lli newUp = up
                + (levelSum[u] - levelSum[v]) // sum from everyone but v
                - (subtreeSize[u] - subtreeSize[v]) * level[u] // shift above's sum to start at 0
                + (n - subtreeSize[v]); // add 1 to above's sum
      dfs3(newUp, v, u);
    }
}

lli ans[maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++) tree[i].clear();
    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
    }

    dfs();
    dfs2();
    dfs3();
    for (int i = 0; i < n; i++)
    {
      lli below = levelSum[i] - subtreeSize[i] * level[i];
      ans[i] = below + above[i];
      DEBUG printf("\t%d - %lld %lld\n", i + 1, below, above[i]);
    }

    for (int i = 0; i < n; i++)
      printf("%lld\n", ans[i]);
  }
  return 0;
}