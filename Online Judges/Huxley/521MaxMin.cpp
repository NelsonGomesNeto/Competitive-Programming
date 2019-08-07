#include <bits/stdc++.h>
using namespace std;
int inf = 1<<20;

void dijkstra(vector<int> graph[], int source, int cost[])
{
  deque<pair<int, int> > q; q.push_back({source, 0});
  while (!q.empty())
  {
    int u = q.front().first, c = q.front().second; q.pop_front();
    // printf("%d %d\n", u, c);
    if (cost[u] != inf) continue;
    cost[u] = c;
    for (auto v: graph[u]) q.push_back({v, c + 1});
  }
}

int main()
{
  int t; scanf("%d", &t);
  int r = 0;
  while (r < t)
  {
    int n, s; scanf("%d %d", &n, &s);
    vector<int> graph[n];
    int deg, v;
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &deg);
      for (int j = 0; j < deg; j ++)
      {
        scanf("%d", &v);
        graph[i].push_back(v);
      }
    }

    int cost[n]; for (int i = 0; i < n; i ++) cost[i] = inf;
    dijkstra(graph, s, cost);
    int d = 0, nd = 1;
    for (int i = 0; i < n; i ++)
    {
      if (i == s) continue;
      if (cost[i] > d)
      {
        d = cost[i];
        nd = 1;
      }
      else if (cost[i] == d)
        nd ++;
    }
    printf("%d %d %d\n", r, d, nd);
    r ++;
  }
  return(0);
}
