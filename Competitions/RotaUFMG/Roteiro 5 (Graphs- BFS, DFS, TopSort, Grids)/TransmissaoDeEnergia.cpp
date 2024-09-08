#include <bits/stdc++.h>
using namespace std;

int dfs(vector<int> graph[], int u, int visited[])
{
  if (visited[u]) return(0);
  visited[u] = 1;
  int nodes = 1;
  for (auto v: graph[u])
    nodes += dfs(graph, v, visited);
  return(nodes);
}

int main()
{
  int n, m, t = 0;
  while (scanf("%d %d", &n, &m) && !(!n && !m))
  {
    if (t ++) printf("\n");
    vector<int> graph[n]; int u, v;
    for (int i = 0; i < m; i ++)
    {
      scanf("%d %d", &u, &v); u --; v --;
      graph[u].push_back(v); graph[v].push_back(u);
    }

    int visited[n]; memset(visited, 0, sizeof(visited));
    int valid = dfs(graph, 0, visited) == n;
    //for (int i = 0; i < n; i ++) if (!visited[i]) valid = 0;

    printf("Teste %d\n%s\n", t, valid ? "normal" : "falha");
  }
  return(0);
}