#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e5, maxGN = 800, maxM = 2e5; int n, m, k;
const lli inf = 1e17;
pair<lli, pair<int, int>> edges[maxM];
int vertexMap[maxN], vertices;
lli graph[maxGN][maxGN], dist[maxGN][maxGN], nxt[maxGN][maxGN];

void floydWarshall()
{
  for (int i = 0; i < vertices; i ++)
    for (int j = 0; j < vertices; j ++)
      if (i == j) dist[i][j] = 0;
      else if (graph[i][j] != -1) dist[i][j] = graph[i][j], nxt[i][j] = j;
      else dist[i][j] = inf;

  for (int k = 0; k < vertices; k ++)
    for (int i = 0; i < vertices; i ++) 
      for (int j = 0; j < vertices; j ++)
        if (dist[i][k] + dist[k][j] < dist[i][j])
          dist[i][j] = dist[i][k] + dist[k][j], nxt[i][j] = nxt[i][k];
}

int main()
{
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 0; i < m; i ++)
  {
    int u, v; lli c; scanf("%d %d %lld", &u, &v, &c); u --, v --;
    edges[i] = {c, {u, v}};
  }
  sort(edges, edges+m);

  memset(vertexMap, -1, sizeof(vertexMap));
  memset(graph, -1, sizeof(graph));
  for (int i = 0; i < k; i ++)
  {
    if (vertexMap[edges[i].second.first] == -1)
      vertexMap[edges[i].second.first] = vertices ++;
    if (vertexMap[edges[i].second.second] == -1)
      vertexMap[edges[i].second.second] = vertices ++;
    graph[vertexMap[edges[i].second.first]][vertexMap[edges[i].second.second]] = edges[i].first;
    graph[vertexMap[edges[i].second.second]][vertexMap[edges[i].second.first]] = edges[i].first;
  }
  floydWarshall();
  vector<lli> ans;
  for (int i = 0; i < vertices; i ++)
    for (int j = i + 1; j < vertices; j ++)
      ans.push_back(dist[i][j]);
  sort(ans.begin(), ans.end());
  printf("%lld\n", ans[k - 1]);

  return(0);
}