#include <bits/stdc++.h>
using namespace std;

int dfs(vector<int> graph[], int u, int color[], int c, int prev)
{
  if (color[u] != -1) return(color[u] != c);
  color[u] = c;
  for (auto v: graph[u])
    if (v != prev && dfs(graph, v, color, 1 - c, u))
      return(1);
  return(0);
}

int main()
{
  int n, m, t = 0;
  while (scanf("%d %d", &n, &m) != EOF)
  {
    if (t ++) printf("\n");
    vector<int> graph[n]; int u, v;
    for (int i = 0; i < m; i ++)
    {
      scanf("%d %d", &u, &v); u --; v --;
      graph[u].push_back(v); graph[v].push_back(u);
    }

    int color[n]; memset(color, -1, sizeof(color));
    int can = !dfs(graph, 0, color, 0, 0);
    printf("Instancia %d\n%s\n", t, can ? "sim" : "nao");
  }
  return(0);
}