#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5; int n, m, source;
vector<int> graph[maxN];

bool visited[maxN][2], hasCycle; int color[maxN];
vector<int> path;
bool dfs(int u, bool even = false)
{
  if (graph[u].size() == 0) { if (even) path.push_back(u); return(even); }
  if (color[u] == 1) hasCycle = true;
  color[u] = 1;
  if (!visited[u][even])
  {
    visited[u][even] = true;
    for (int v: graph[u]) 
      if (dfs(v, !even))
      {
        path.push_back(u);
        return(true);
      }
  }
  color[u] = 2;
  return(false);
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i ++)
  {
    int u, c; scanf("%d", &c);
    while (c --)
    {
      scanf("%d", &u);
      graph[i].push_back(u - 1);
    }
  }
  scanf("%d", &source); source --;

  memset(memo, -1, sizeof(memo));
  if (dfs(source))
  {
    printf("Win\n");
    reverse(path.begin(), path.end());
    for (int i: path) printf("%d ", i + 1);
    printf("\n");
  }
  else printf("%s\n", hasCycle ? "Draw" : "Lose");

  return(0);
}