#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 500; int n, m;
int a[maxN][maxN], b[maxN][maxN];

int getVertex(int i, int j)
{
  return i*m + j;
}
vector<pair<int, int>> graph[maxN*maxN];

int dist[maxN*maxN];
int dijkstra(int target = getVertex(n - 1, m - 1))
{
  for (int i = 0; i < n*m; i++) dist[i] = 1e9;
  priority_queue<pair<int, int>> pq;
  pq.push({dist[0] = 0, 0});
  while (!pq.empty())
  {
    int u = pq.top().second, d = -pq.top().first; pq.pop();
    if (u == target) break;
    if (d > dist[u]) continue;

    for (auto &[v, c]: graph[u])
      if (d + c < dist[v])
        pq.push({-(dist[v] = d + c), v});
  }
  return dist[getVertex(n - 1, m - 1)];
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m - 1; j++)
        scanf("%d", &a[i][j]);
    for (int i = 0; i < n - 1; i++)
      for (int j = 0; j < m; j++)
        scanf("%d", &b[i][j]);


    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
      {
        graph[getVertex(i, j)].clear();
        if (j + 1 < m) graph[getVertex(i, j)].push_back({getVertex(i, j + 1), a[i][j]});
        if (j - 1 >= 0) graph[getVertex(i, j)].push_back({getVertex(i, j - 1), a[i][j - 1]});
        if (i + 1 < n) graph[getVertex(i, j)].push_back({getVertex(i + 1, j), b[i][j]});
        for (int k = 1; k <= i; k++)
          graph[getVertex(i, j)].push_back({getVertex(i - k, j), 1 + k});
      }

    int ans = dijkstra();
    DEBUG
      for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
          printf("%d %d - %d\n", i, j, dist[getVertex(i, j)]);
    printf("%d\n", ans);
  }
  return 0;
}