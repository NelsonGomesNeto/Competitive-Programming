#include <bits/stdc++.h>
using namespace std;
int n, m;

int prim(vector<pair<int, int> > graph[])
{
  int visited[n]; memset(visited, 0, sizeof(visited));
  priority_queue<pair<int, int>, vector<pair<int, int> >, less<pair<int, int> > > pq;
  pq.push({0, 0});
  int cost = 0;
  while (!pq.empty())
  {
    int u = pq.top().second, c = pq.top().first; pq.pop();
    if (visited[u]) continue;
    visited[u] = 1;
    cost += c;
    for (auto vp: graph[u])
    {
      int v = vp.first, cc = vp.second;
      pq.push({cc, v});
    }
  }
  return(cost);
}

int main()
{
  scanf("%d %d", &n, &m);
  int c, r; scanf("%d %d", &c, &r);
  vector<pair<int, int> > p1[n];
  vector<pair<int, int> > p2[n];
  for (int i = 0; i < m; i ++)
  {
    int u, v, cost; scanf("%d %d %d", &u, &v, &cost);
    cost = c * cost;
    p1[u].push_back({v, cost});
    // p1[v].push_back({u, cost});
    p2[u].push_back({v, r});
    // p2[v].push_back({u, r});
  }

  printf("%d %d\n", prim(p1), prim(p2));
  return(0);
}