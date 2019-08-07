#include <bits/stdc++.h>
using namespace std;

int dfs(vector<int> graph[], int u, int visited[], int pathToAll[])
{
  if (pathToAll[u]) return(1);
  if (visited[u]) return(0);
  visited[u] = 1;
  for (auto v: graph[u])
    if (dfs(graph, v, visited, pathToAll))
      return(1);
  return(0);
}

int main()
{
  int n, m;
  while (scanf("%d %d", &n, &m) && n)
  {
    vector<int> graph[n]; int u, v, p;
    for (int i = 0; i < m; i ++)
    {
      scanf("%d %d %d", &u, &v, &p); u --; v --;
      graph[u].push_back(v);
      if (p == 2) graph[v].push_back(u);
    }

    int valid = 1, pathToAll[n], visited[n];
    memset(pathToAll, 0, sizeof(pathToAll));
    for (int i = 0; i < n && valid; i ++)
    {
      memset(visited, 0, sizeof(visited));
      if (!dfs(graph, i, visited, pathToAll))
        for (int j = 0; j < n; j ++)
          if (!visited[j]) valid = 0;
      pathToAll[i] = 1;
    }

    printf("%d\n", valid);
  }
  return(0);
}