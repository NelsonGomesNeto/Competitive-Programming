#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
const lli inf = 1e16;
lli c[3][maxN];
int color[maxN];
vector<int> graph[maxN];

lli dfs(int u, vector<int> &p, int prv = -1, int at = 0)
{
  lli cost = c[p[at]][u];
  color[u] = p[at];
  for (int v: graph[u])
    if (v != prv)
      cost += dfs(v, p, u, (at + 1) % 3);
  return cost;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i ++) graph[i].clear();
    for (int i = 0; i < 3; i ++)
      for (int j = 0; j < n; j ++)
        scanf("%lld", &c[i][j]);
    for (int i = 1; i < n; i ++)
    {
      int u, v; scanf("%d %d", &u, &v); u --, v --;
      // printf("\t%d %d\n", u, v);
      graph[u].push_back(v), graph[v].push_back(u);
    }
    bool can = true;
    for (int i = 0; i < n; i ++)
      if (graph[i].size() > 2)
        can = false;
    if (!can) printf("-1\n");
    else
    {
      int start = 0;
      for (int i = 0; i < n; i ++)
        if (graph[i].size() == 1)
          start = i;
      vector<int> p = {0, 1, 2}, chosen;
      lli best = inf;
      do
      {
        lli c = dfs(start, p);
        if (c < best)
          best = c, chosen = p;
      }
      while (next_permutation(p.begin(), p.end()));
      printf("%lld\n", best);
      dfs(start, chosen);
      for (int i = 0; i < n; i ++)
        printf("%d%c", color[i] + 1, i < n - 1 ? ' ' : '\n');
    }
  }
  return 0;
}
