#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
vector<int> tree[maxN];

int l[maxN], r[maxN], leafs;
void dfs(int u = 0, int prv = -1)
{
  if (prv != -1 && tree[u].size() == 1)
    l[u] = r[u] = ++leafs;

  for (int v: tree[u])
    if (v != prv)
    {
      dfs(v, u);

      if (l[u] == -1) l[u] = l[v];
      else l[u] = min(l[u], l[v]);

      if (r[u] == -1) r[u] = r[v];
      else r[u] = max(r[u], r[v]);
    }
}

int main()
{
  int tt = 0;
  while (~scanf("%d", &n))
  {
    if (tt++) printf("--------------------\n");

    leafs = 0;
    for (int i = 0; i < n; i++) tree[i].clear();
    memset(l, -1, sizeof(l)), memset(r, -1, sizeof(r));

    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
    }

    dfs();

    for (int i = 0; i < n; i++)
      printf("%d %d\n", l[i], r[i]);
  }
  return 0;
}