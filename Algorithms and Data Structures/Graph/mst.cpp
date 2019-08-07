#include <bits/stdc++.h>
using namespace std;

void printSpacing(int i) { while (i --) printf("   "); }
void printGraph(vector<pair<int, int>> g[], pair<int, int> u, int prev, int depth)
{
  printSpacing(depth); printf("(%d, %d)\n", u.first + 1, u.second);
  for (auto v: g[u.first]) if (v.first != prev) printGraph(g, v, u.first, depth + 1);
}

const int maxV = 1e5; int n, m;
vector<pair<int, int>> graph[maxV], mst[maxV];

int prim(int source)
{
  bool visited[n]; memset(visited, false, sizeof(visited)); visited[source] = true;
  priority_queue<pair<int, pair<int, int>>> pq;
  for (auto v: graph[source]) pq.push({-v.second, {v.first, source}});
  int mstCost = 0;
  while (!pq.empty())
  {
    int u = pq.top().second.first, prev = pq.top().second.second, c = -pq.top().first; pq.pop();
    if (visited[u]) continue;
    mst[u].push_back({prev, c}); mst[prev].push_back({u, c}); mstCost += c;
    visited[u] = true;
    for (auto v: graph[u]) pq.push({-v.second, {v.first, u}});
  }
  return(mstCost);
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i ++)
  {
    int u, v, c; scanf("%d %d %d", &u, &v, &c); u --, v --;
    graph[u].push_back({v, c}); graph[v].push_back({u, c});
  }
  int mstCost = prim(0);

  printf("%d\n", mstCost);
  printf("%d\n", 1);
  for (auto v: mst[0])
    printGraph(mst, v, 0, 1);
  return(0);
}
