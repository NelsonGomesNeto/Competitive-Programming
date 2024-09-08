#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 400; int n, m;
const int inf = 1e8;
struct Edge
{
  int u, v;
  void read() { scanf("%d %d", &u, &v); u--, v--; }
};
Edge edges[maxN*maxN];
int edgeMap[maxN][maxN];
bool blocked[maxN][maxN];
vector<int> graph[maxN];
int ans[maxN*maxN];

int prv[maxN], dist[maxN];
int bfs()
{
  for (int i = 0; i < n; i++) dist[i] = inf;

  queue<int> q;
  q.push(0), dist[0] = 0;
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    DEBUG printf("\t\t%d %d\n", u, dist[u]);
    if (u == n - 1) break;

    for (int v: graph[u])
    {
      DEBUG printf("\t\t\t%d %d %d\n", u, v, blocked[u][v]);
      if (!blocked[u][v] && dist[u] + 1 < dist[v])
      {
        dist[v] = dist[u] + 1;
        prv[v] = u;
        q.push(v);
      }
    }
  }
  DEBUG
    for (int i = 0; i < n; i++)
      printf("\t%d %d\n", i + 1, dist[i]);
  return dist[n - 1];
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    memset(blocked, false, sizeof(blocked));
    for (int i = 0; i < n; i++) graph[i].clear();

    for (int i = 0; i < m; i++)
    {
      edges[i].read();
      graph[edges[i].u].push_back(edges[i].v);
      edgeMap[edges[i].u][edges[i].v] = i;
    }

    bfs();

    if (dist[n - 1] == inf)
    {
      for (int i = 0; i < m; i++)
        printf("%d%c", -1, i < m - 1 ? '\n' : '\n');
    }
    else
    {
      for (int i = 0; i < m; i++)
        ans[i] = dist[n - 1];

      for (int u = n - 1; u != 0; u = prv[u])
      {
        int uu = prv[u], vv = u;
        ans[edgeMap[uu][vv]] = -1;
      }

      for (int i = 0; i < m; i++)
        if (ans[i] == -1)
        {
          blocked[edges[i].u][edges[i].v] = true;
          ans[i] = bfs();
          if (ans[i] == inf) ans[i] = -1;
          blocked[edges[i].u][edges[i].v] = false;
        }

      for (int i = 0; i < m; i++)
        printf("%d%c", ans[i], i < m - 1 ? '\n' : '\n');
    }
  }
  return 0;
}