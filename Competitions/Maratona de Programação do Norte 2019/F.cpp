#include <bits/stdc++.h>
using namespace std;

/* Tutorial:
  An already present edge has cost -c (to remove it, you would pay c)
  A not present edge has cost c
  Using above idea, you can just sort the edges and apply any MST algorithm
  Just remember to calculate the cost properly:
    add the cost of edges from the mst that aren't present on the original graph
    add the cost of edges that aren't on the mst but are present on original graph
*/

const int maxN = 450; int n;
int graph[maxN][maxN];
bool chosen[maxN][maxN];
bool visited[maxN];

void prim()
{
  priority_queue<pair<int, pair<int, int>>> pq;
  pq.push({0, {0, -1}});
  while (!pq.empty())
  {
    int u = pq.top().second.first, prv = pq.top().second.second, c = pq.top().first; pq.pop();
    if (visited[u]) continue;
    visited[u] = true;
    if (prv != -1) chosen[max(u, prv)][min(u, prv)] = true;
    for (int v = 0; v < n; v ++)
      if (v != u)
        pq.push({-(graph[min(u, v)][max(u, v)] * (graph[max(u, v)][min(u, v)] ? -1 : 1)), {v, u}});
  }
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
      scanf("%d", &graph[i][j]);

  prim();
  int ans = 0;
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < i; j ++)
      if ((graph[i][j] && !chosen[i][j]) || (chosen[i][j] && !graph[i][j]))
        ans += graph[j][i];
  printf("%d\n", ans);

  return(0);
}