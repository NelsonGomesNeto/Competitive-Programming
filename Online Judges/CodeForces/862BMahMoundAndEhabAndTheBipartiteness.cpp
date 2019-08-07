#include <bits/stdc++.h>
using namespace std;
long long int blue = 0, red = 0;

void dfs(vector<int> graph[], int u, int color, int visited[])
{
  if (visited[u]) return;
  visited[u] = 1;
  blue += color;
  for (auto v: graph[u])
    dfs(graph, v, 1 - color, visited);
}

int main()
{
  int n; scanf("%d", &n);
  vector<int> graph[n]; int u, v, visited[n];
  for (int i = 0; i < n - 1; i ++)
  {
    scanf("%d %d", &u, &v); u --; v --;
    graph[u].push_back(v); graph[v].push_back(u);
  }

  memset(visited, 0, sizeof(visited));
  dfs(graph, 0, 1, visited);
  red = n - blue;
  //printf("%d %d\n", blue, red);

  //printf("%lld\n", (blue - 1) * (red - 1));
  printf("%lld\n", blue * red - n + 1);

  return(0);
}