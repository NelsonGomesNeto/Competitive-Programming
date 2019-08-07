#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5, inf = 1e6; int n, m, mineirin, cubano, destination;
vector<int> graph[maxN];
bool visited[maxN];

int bfs(int origin)
{
  memset(visited, false, sizeof(visited));
  queue<pair<int, int>> q; q.push({origin, 0});
  while (!q.empty())
  {
    int u = q.front().first, d = q.front().second; q.pop();
    if (u == destination) return(d);
    if (visited[u]) continue;
    visited[u] = true;
    for (int v: graph[u])
      q.push({v, d + 1});
  }
  return(inf);
}

int main()
{
  scanf("%d %d %d %d %d", &n, &m, &mineirin, &cubano, &destination);
  for (int i = 0, u, v; i < m; i ++)
  {
    scanf("%d %d", &u, &v);
    graph[u].push_back(v), graph[v].push_back(u);
  }
  int mineirinDistance = bfs(mineirin), cubanoDistance = bfs(cubano);
  if (mineirinDistance == cubanoDistance) printf("Nao, mas... Serio?\n");
  else if (mineirinDistance < cubanoDistance) printf("Nao, mas...\n");
  else printf("Serio?\n");

  return(0);
}