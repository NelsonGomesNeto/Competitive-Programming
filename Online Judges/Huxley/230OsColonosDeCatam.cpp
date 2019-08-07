#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 26; int n, m;
vector<int> graph[maxN];
bool usedEdge[maxN][maxN];

int solve(int u)
{
  int ans = 0;
  for (int v: graph[u])
    if (!usedEdge[u][v])
    {
      usedEdge[u][v] = usedEdge[v][u] = true;
      ans = max(ans, 1 + solve(v));
      usedEdge[u][v] = usedEdge[v][u] = false;
    }
  return(ans);
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF && !(!n && !m))
  {
    for (int i = 0; i <= n; i ++) graph[i].clear();
    for (int i = 0, u, v; i < m; i ++)
    {
      scanf("%d %d", &u, &v);
      graph[u].push_back(v), graph[v].push_back(u);
    }

    int ans = 0;
    for (int i = 0; i <= n; i ++)
    {
      memset(usedEdge, false, sizeof(usedEdge));
      ans = max(ans, solve(i));
    }
    printf("%d\n", ans);
  }
  return(0);
}