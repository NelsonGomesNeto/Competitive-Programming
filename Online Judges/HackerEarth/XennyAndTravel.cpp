#include <bits/stdc++.h>
using namespace std;

/* Explanation:
Problem description is wrong: he must pass at least once throught both transportations (and not exactly)
*/

const int maxN = 1250; int n;
int roadways[maxN][maxN], revRoadways[maxN][maxN], railways[maxN][maxN], revRailways[maxN][maxN];
int roadDistSource[maxN], railDistSource[maxN], roadDistTarget[maxN], railDistTarget[maxN];

void dijkstra(int source, int graph[maxN][maxN], int cost[maxN])
{
  for (int i = 0; i < n; i ++) cost[i] = 1e7;
  priority_queue<pair<int, int>> pq; pq.push({0, source}); cost[source] = 0;
  while (!pq.empty())
  {
    int u = pq.top().second; pq.pop();
    for (int v = 0; v < n; v ++)
      if (v != u && cost[u] + graph[u][v] < cost[v])
      {
        cost[v] = cost[u] + graph[u][v];
        pq.push({-cost[v], v});
      }
  }
}

void read(int a[maxN][maxN], int b[maxN][maxN])
{
  for (int i = 0; i < n; i ++) for (int j = 0; j < n; j ++) { scanf("%d", &a[i][j]); b[j][i] = a[i][j]; }
}

int main()
{
  scanf("%d", &n);
  read(roadways, revRoadways); read(railways, revRailways);

  int source, target; scanf("%d %d", &source, &target); source --, target --;
  dijkstra(source, roadways, roadDistSource); dijkstra(source, railways, railDistSource);
  dijkstra(target, revRoadways, roadDistTarget); dijkstra(target, revRailways, railDistTarget);
  int ans = 1e7;
  for (int i = 0; i < n; i ++)
    if (i != source && i != target)
      ans = min(ans, min(roadDistSource[i] + railDistTarget[i], railDistSource[i] + roadDistTarget[i]));
  printf("%d\n", ans);
  return(0);
}