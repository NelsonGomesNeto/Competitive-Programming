#include <bits/stdc++.h>
using namespace std;
#define pb(a) push_back(a)
#define inf 1000000000

void dijkstra(vector<vector<int> > graph, int cost[], int visited[], int start)
{
  cost[start] = 0;
  priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
  pq.push({cost[start], start});
  while (!pq.empty())
  {
    int v = pq.top().second; pq.pop();
    if (visited[v]) continue;
    visited[v] = 1;
    for (auto u : graph[v])
    {
      if (cost[v] + 1 < cost[u])
      {
        cost[u] = cost[v] + 1;
        pq.push({cost[u], u});
      }
    }
  }
}

int main()
{
  int tests; cin >> tests;
  while (tests > 0)
  {
    int islands, bridges; cin >> islands >> bridges;
    vector<vector<int> > graph(islands + 1); int u, v;
    for (int i = 0; i < bridges; i ++)
    {
      cin >> u >> v;
      graph[u].pb(v);
      graph[v].pb(u);
    }
    int cost[islands + 1], visited[islands + 1];
    for (int i = 0; i <= islands; i ++)
    {
      cost[i] = inf;
      visited[i] = 0;
    }
    dijkstra(graph, cost, visited, 1);
    printf("%d\n", cost[islands] == inf ? -1 : cost[islands]);

    tests --;
  }
  return(0);
}