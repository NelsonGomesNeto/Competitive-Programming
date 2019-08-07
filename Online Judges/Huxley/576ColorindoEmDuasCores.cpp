#include <bits/stdc++.h>
using namespace std;

int bicolorable(vector<int> graph[], int u, int now, int color[])
{
  if (color[u] != -1) return(color[u] != 1 - now);
  color[u] = now;
  for (auto v: graph[u])
    if (!bicolorable(graph, v, 1 - now, color))
      return(0);
  return(1);
}

int main()
{
  int n, m;
  while (scanf("%d", &n) && n)
  {
    scanf("%d", &m);
    vector<int> graph[n]; int u, v;
    for (int i = 0; i < m; i ++)
    {
      scanf("%d %d", &u, &v);
      graph[u].push_back(v);
      graph[v].push_back(u);
    }

    int color[n]; memset(color, -1, sizeof(color));
    printf("%s.\n", bicolorable(graph, 0, 0, color) ? "BICOLORABLE" : "NOT BICOLORABLE");
  }
  return(0);
}
