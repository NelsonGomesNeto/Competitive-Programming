#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5, maxK = 500, inf = 1e7; int n, m, k;
int groups[maxK], vertexGroup[maxN];
vector<pair<int, int>> graph[maxN], groupsGraph[maxK];

bool visited[maxN], triedGruop[maxK];
bool bfs(int source, int last)
{
  for (int i = source; i <= last; i ++) visited[i] = false;
  queue<int> q; q.push(source);
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    if (visited[u]) continue;
    visited[u] = true;
    for (auto v: graph[u]) if (v.second == 0) q.push(v.first);
  }
  for (int i = source; i <= last; i ++) if (!visited[i]) return(false);
  return(true);
}

int d[maxK][maxK]; int edges[maxK][maxK];
void floydWarshall()
{
  for (int i = 0; i < k; i ++)
    for (int j = 0; j < k; j ++)
      if (i == j) d[i][j] = 0;
      else if (edges[i][j] != -1) d[i][j] = edges[i][j];
      else d[i][j] = inf;

  for (int kk = 0; kk < k; kk ++)
    for (int i = 0; i < k; i ++)
      for (int j = 0; j < k; j ++)
        if (d[i][kk] + d[kk][j] < d[i][j])
          d[i][j] = d[i][kk] + d[kk][j];
}

int main()
{
  memset(edges, -1, sizeof(edges));
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 0, ii = 0; i < k; i ++)
  {
    scanf("%d", &groups[i]);
    for (int j = 0; j < groups[i]; j ++, ii ++) vertexGroup[ii] = i;
  }
  for (int i = 0, u, v, c; i < m; i ++)
  {
    scanf("%d %d %d", &u, &v, &c); u --, v --;
    graph[u].push_back({v, c}), graph[v].push_back({u, c});
    groupsGraph[vertexGroup[u]].push_back({vertexGroup[v], c}),
    groupsGraph[vertexGroup[v]].push_back({vertexGroup[u], c});
    if (edges[vertexGroup[u]][vertexGroup[v]] == -1 || c < edges[vertexGroup[u]][vertexGroup[v]])
      edges[vertexGroup[u]][vertexGroup[v]] = edges[vertexGroup[v]][vertexGroup[u]] = c;
  }

  bool can = true;
  for (int i = 0, source = 0; i < k && can; i ++)
  {
    can = bfs(source, source + groups[i] - 1);
    source += groups[i];
  }
  if (!can) printf("No\n");
  else
  {
    printf("Yes\n");
    floydWarshall();
    for (int i = 0; i < k; i ++)
      for (int j = 0; j < k; j ++)
        printf("%d%c", d[i][j] == inf ? -1 : d[i][j], j < k - 1 ? ' ' : '\n');
  }
  return(0);
}