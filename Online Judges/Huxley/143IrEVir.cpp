#include <bits/stdc++.h>
using namespace std;
int n, m;

int bfs(vector<int> graph[], int source)
{
  int visited[n]; memset(visited, 0, sizeof(visited));
  deque<int> q; q.push_back(source);
  while (!q.empty())
  {
    int u = q.front(); q.pop_front();
    if (visited[u]) continue;
    visited[u] = 1;
    for (auto v: graph[u])
      q.push_back(v);
  }
  for (int i = 0; i < n; i ++) if (!visited[i]) return(0);
  return(1);
}

int main()
{
  while (scanf("%d %d", &n, &m) && n && m)
  {
    vector<int> graph[n];
    int u, v, c;
    for (int i = 0; i < m; i ++)
    {
      scanf("%d %d %d", &u, &v, &c); u --; v --;
      graph[u].push_back(v);
      if (c == 2) graph[v].push_back(u);
    }

    int conex = 1;
    for (int i = 0; i < n && conex; i ++)
      if (!bfs(graph, i)) conex = 0;
    printf("%d\n", conex);
  }
  return(0);
}
