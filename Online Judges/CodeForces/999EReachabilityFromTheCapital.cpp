#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

int dfs(vector<int> graph[], int visited[], int u, int color, int bug[], int lol)
{
  if (visited[u] && (!lol || !bug[u] || (bug[u] && visited[u] == color))) return(0);
  visited[u] = color;
  bug[u] = lol;
  for (auto v: graph[u])
    dfs(graph, visited, v, color, bug, lol);
  return(0);
}

int main()
{
  int n, m, s; scanf("%d %d %d", &n, &m, &s); s --;
  vector<int> graph[n], revGraph[n]; int u, v;
  for (int i = 0; i < m; i ++)
  {
    scanf("%d %d", &u, &v); u --; v --;
    graph[u].push_back(v);
    revGraph[v].push_back(u);
  }

  int visited[n]; memset(visited, 0, sizeof(visited));
  int bug[n]; memset(bug, 0, sizeof(bug));
  dfs(graph, visited, s, s + 1, bug, 0);
  for (int i = 0; i < n; i ++)
    if (!visited[i] && revGraph[i].size() == 0) dfs(graph, visited, i, i + 1, bug, 0);
  DEBUG for (int i = 0; i < n; i ++) printf("%d%c", visited[i], i < n - 1 ? ' ' : '\n');

  for (int i = 0; i < n; i ++)
    if (!visited[i]) dfs(graph, visited, i, i + 1, bug, 1);
  DEBUG for (int i = 0; i < n; i ++) printf("%d%c", visited[i], i < n - 1 ? ' ' : '\n');

  int diff[n + 1], total = 0; memset(diff, 0, sizeof(diff));
  for (int i = 0; i < n; i ++) if (!diff[visited[i]]) { diff[visited[i]] = 1; total ++; }
  printf("%d\n", total - 1);

  return(0);
}