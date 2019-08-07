#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e3, inf = 1e8; int n, m;
vector<pair<int, int>> graph[maxN];
int source = 0, dist[maxN], prv[maxN];

bool bellmanFord()
{
  for (int i = 0; i < n; i ++) dist[i] = inf;
  dist[source] = 0;
  for (int i = 0; i < n - 1; i ++)
    for (int u = 0; u < n; u ++)
      for (auto &v: graph[u])
        if (dist[u] + v.second < dist[v.first])
          dist[v.first] = dist[u] + v.second, prv[v.first] = u;

  // Checks ifs there's a negative cycle
  for (int u = 0; u < n; u ++)
    for (auto &v: graph[u])
      if (dist[u] + v.second < dist[v.first])
        return(true);
  return(false);
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0, u, v, c; i < m; i ++)
  {
    scanf("%d %d %d", &u, &v, &c);
    graph[u].push_back({v, c});
  }

  printf("Has negative cycle: %d\n", bellmanFord());

  return(0);
}