#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

void dfs(vector<int> graph[], int u, int visited[])
{
  if (visited[u]) return;
  visited[u] = 1;
  for (auto v: graph[u])
    dfs(graph, v, visited);
}

int main()
{
  int n; scanf("%d", &n);
  int x[n], y[n]; for (int i = 0; i < n; i ++) scanf("%d %d", &x[i], &y[i]);

  vector<int> graph[n];
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
    {
      if (i == j) continue;
      if (x[i] == x[j] || y[i] == y[j])
        graph[i].push_back(j);
    }

  DEBUG for (int i = 0; i < n; i ++)
  {
    printf("%d", i);
    for (auto j: graph[i])
      printf(" -> %d", j);
    printf("\n");
  }

  int ans = -1, visited[n]; memset(visited, 0, sizeof(visited));
  for (int i = 0; i < n; i ++)
    if (!visited[i])
    {
      dfs(graph, i, visited);
      ans ++;
    }

  printf("%d\n", ans);

  return(0);
}