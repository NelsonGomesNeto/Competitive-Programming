#include <bits/stdc++.h>
using namespace std;
int cheese[(int) 1e5], n, m, c, inf = 1<<20;

int dijkstra(vector<int> graph[], int source, int target, int kind)
{
  int cost[n], visited[n]; memset(visited, 0, sizeof(visited));
  for (int i = 0; i < n; i ++) cost[i] = !kind ? inf : -inf;
  cost[source] = cheese[source];
  priority_queue<pair<int, int>, vector<pair<int, int> >, less<pair<int, int> > > pql;
  priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pqg;
  if (!kind) pqg.push({cost[source], source}); else pql.push({cost[source], source});
  while ((!kind && !pqg.empty()) || (kind && !pql.empty()))
  {
    int c = !kind ? pqg.top().first : pql.top().first, v = !kind ? pqg.top().second : pql.top().second;
    //printf("%d %d\n", v, c);
    if (!kind) pqg.pop(); else pql.pop();
    //if (visited[v]) continue;
    //visited[v] = 1;
    for (auto u: graph[v])
    {
      if ((!kind && c + cheese[u] < cost[u]) || (kind && c + cheese[u] > cost[u]))
      {
        cost[u] = c + cheese[u];
        if (!kind) pqg.push({cost[u], u}); else pql.push({cost[u], u});
      }
    }
  }
  return(cost[target]);
}

int main()
{
  memset(cheese, 0, sizeof(cheese));
  scanf("%d %d %d", &n, &m, &c);
  for (int i = 0; i < m; i ++)
  {
    int at; scanf("%d", &at); at --;
    cheese[at] = 1;
  }

  vector<int> graph[n];
  for (int i = 0; i < c; i ++)
  {
    int u, v; scanf("%d %d", &u, &v); u --; v --;
    graph[u].push_back(v);
  }

  int minimum = dijkstra(graph, 0, n - 1, 0); //printf("\n");
  int maximum = dijkstra(graph, 0, n - 1, 1);
  printf("%d %d\n", minimum, maximum);

  return(0);
}