#include <bits/stdc++.h>
using namespace std;

const int maxN = 2e4; int n, m, s;
vector<int> graph[maxN], full[maxN];
int indegree[maxN];
bool visited[maxN];

void dfs(int u = s, vector<int> g[] = graph)
{
  if (visited[u]) return;
  visited[u] = true;
  for (int v: g[u]) dfs(v, g);
}

int main()
{
  scanf("%d %d %d", &n, &m, &s); s --;
  for (int i = 0, u, v; i < m; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    if (u == v) continue;
    graph[u].push_back(v), indegree[v] ++;
    full[u].push_back(v), full[v].push_back(u);
  }
  dfs();

  int ans = 0;
  for (int i = 0; i < n; i ++)
    if (!visited[i] && indegree[i] == 0)
      ans ++, dfs(i);
  for (int i = 0; i < n; i ++)
    if (!visited[i])
      ans ++, dfs(i, full);
  printf("%d\n", ans);

  return(0);
}