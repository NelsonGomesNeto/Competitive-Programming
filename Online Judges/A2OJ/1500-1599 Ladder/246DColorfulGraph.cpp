#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5; int n, m;
int colors[maxN]; bool validColor[maxN]; set<int> neighborColors[maxN];
vector<int> graph[maxN];

bool visited[maxN];
void dfs(int u)
{
  if (visited[u]) return;
  visited[u] = true;
  for (int v: graph[u])
  {
    dfs(v);
    if (colors[u] != colors[v]) neighborColors[colors[u]].insert(colors[v]);
  }
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i ++) { scanf("%d", &colors[i]); validColor[-- colors[i]] = true; }
  for (int i = 0, u, v; i < m; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    graph[u].push_back(v), graph[v].push_back(u);
  }

  for (int i = 0; i < n; i ++) if (!visited[i]) dfs(i);

  int bestColor = -1;
  for (int i = 0; i < 1e5; i ++)
    if (validColor[i] && (bestColor == -1 || neighborColors[bestColor].size() < neighborColors[i].size()))
      bestColor = i;
  printf("%d\n", bestColor + 1);

  return(0);
}