#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
int colors[maxN];
vector<int> tree[maxN];

int subtreeSize[maxN];
void dfs1(int u = 0, int prv = -1)
{
  subtreeSize[u] = 1;
  for (int v: tree[u])
    if (v != prv)
    {
      dfs1(v, u);
      subtreeSize[u] += subtreeSize[v];
    }
}

int lol[maxN]; // the number of vertices in u's subtree can reach before meeting c[v] == c[parent[u]]
int colorSubtree[maxN];
void dfs2(int u = 0, int prv = -1)
{
  if (prv != -1);

  int before = colorSubtree[colors[u]];
  for (int v: tree[u])
    if (v != prv)
    {
      dfs2(v, u);
    }
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++) tree[i].clear();
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &colors[i]);
      colors[i]--;
    }
    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
    }

    dfs1();
    dfs2();

    for (int i = 0; i < n; i++) printf("%lld\n", ans[i]);
  }
  return 0;
}