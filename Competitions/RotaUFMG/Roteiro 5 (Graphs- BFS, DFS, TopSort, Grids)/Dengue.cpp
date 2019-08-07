#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

int dfs(vector<int> graph[], int u, int visited[], int l)
{
  if (visited[u]) return(0);
  visited[u] = 1;
  int cost = l;
  for (auto v: graph[u])
    cost = max(cost, dfs(graph, v, visited, l + 1));
  return(cost);
}

int main()
{
  int n, t = 0;
  while (scanf("%d", &n) && n)
  {
    if (t ++) printf("\n");

    vector<int> tree[n]; int u, v;
    for (int i = 0; i < n - 1; i ++)
    {
      scanf("%d %d", &u, &v); u --; v --;
      tree[u].push_back(v);
      tree[v].push_back(u);
    }

    int visited[n], ans = 0, best = 9999999;
    for (int i = 0; i < n; i ++)
    {
      memset(visited, 0, sizeof(visited));
      int cost = dfs(tree, i, visited, 0);
      DEBUG printf("%d %d\n", i, cost);
      if (cost < best)
      {
        best = cost;
        ans = i;
      }
    }

    printf("Teste %d\n%d\n", t, ans + 1);
  }
  return(0);
}