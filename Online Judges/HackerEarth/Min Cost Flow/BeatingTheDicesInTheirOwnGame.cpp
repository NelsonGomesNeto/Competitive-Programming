#include <bits/stdc++.h>
using namespace std;
#define lli long long int
const int maxFaces = 100 * 100, maxN = 100; lli inf = 1e16;
// source (0) -> dice (1-100) -> faces (101-100+100*100) -> target (100+100*100 + 1)
const int maxVertices = 1 + maxN + maxFaces + 1;
int source = 0, target, vertices, prevVertex[maxVertices], prevEdge[maxVertices];
lli cost[maxVertices], minFlow[maxVertices];
unordered_map<lli, int> faceMap;

struct Edge { int to, back, flow, capacity; lli cost; };
vector<Edge> graph[maxVertices];
void addEdge(int u, int v, int f, lli c)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f, c});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0, -c});
}

void bfsFix()
{
  int visited[vertices]; memset(visited, 0, sizeof(visited));
  deque<int> q; q.push_back(source);
  while (!q.empty())
  {
    int u = q.front(); q.pop_front();
    if (visited[u]) continue;
    visited[u] = 1;
    for (auto &e: graph[u]) e.flow = e.capacity, q.push_back(e.to);
  }
}

int bellmanFord()
{
  for (int i = 0; i < vertices; i ++) cost[i] = minFlow[i] = inf;
  cost[source] = 0;
  for (int i = 0, done = 0; i < vertices - 1; i ++, done = 0)
  {
    for (int u = 0; u < vertices; u ++)
      for (int j = 0; j < graph[u].size(); j ++)
      {
        Edge &e = graph[u][j];
        if (e.flow && cost[u] + e.cost < cost[e.to])
        {
          cost[e.to] = cost[u] + e.cost;
          prevVertex[e.to] = u, prevEdge[e.to] = j;
          minFlow[e.to] = min(minFlow[u], (lli) e.flow);
          done = 1;
        }
      }
    if (!done) break;
  }
  return(cost[target] != inf);
}

pair<lli, lli> minCostFlow()
{
  lli minCost = 0, totalFlow = 0;
  while (bellmanFord())
  {
    lli flow = minFlow[target];
    totalFlow += flow;
    for (int v = target; v != source; v = prevVertex[v])
    {
      Edge &e = graph[prevVertex[v]][prevEdge[v]];
      e.flow -= flow;
      graph[e.to][e.back].flow += flow;
      minCost += e.cost * flow;
    }
  }
  return(make_pair(minCost, totalFlow));
}

int main()
{
  int n; scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    int die = 1 + i;
    addEdge(source, die, 1, 0);
    int m; scanf("%d", &m); lli u, c;
    for (int j = 0; j < m; j ++)
    {
      scanf("%lld %lld", &u, &c);
      int faceNumber = faceMap.size();
      if (!faceMap.count(u)) faceMap[u] = 1 + n + faceNumber;
      addEdge(die, faceMap[u], 1, c);
    }
  }
  target = 1 + n + faceMap.size(); vertices = target + 1;
  int faceToTarget[vertices];
  for (auto i: faceMap) addEdge(i.second, target, 0, 0), faceToTarget[i.second] = graph[i.second].size() - 1;

  int q; scanf("%d", &q);
  while (q --)
  {
    lli face[n]; int can = 1;
    for (int i = 0; i < n; i ++)
    {
      scanf("%lld", &face[i]);
      if (!faceMap.count(face[i])) can = 0;
    }
    if (!can) printf("-1\n");
    else
    {
      bfsFix();
      for (int i = 0; i < n; i ++)
      {
        face[i] = faceMap[face[i]];
        graph[face[i]][faceToTarget[face[i]]].flow ++;
      }
      pair<lli, lli> ans = minCostFlow();
      // printf("%lld %lld\n", ans.first, ans.second);
      printf("%lld\n", ans.second == n ? ans.first : -1);
    }
  }
  return(0);
}
