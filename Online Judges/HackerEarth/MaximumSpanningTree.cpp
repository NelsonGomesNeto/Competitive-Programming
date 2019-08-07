#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 5e3; int n, m;
vector<pair<int, lli>> graph[maxN];

lli prim()
{
  bool visited[n]; memset(visited, false, sizeof(visited)); visited[0] = true;
  priority_queue<pair<lli, pair<int, int>>> pq;
  for (auto v: graph[0]) pq.push({v.second, {v.first, 0}});
  int cost = 0;
  while (!pq.empty())
  {
    int u = pq.top().second.first, prev = pq.top().second.second, c = pq.top().first; pq.pop();
    if (visited[u]) continue;
    cost += c;
    visited[u] = true;
    for (auto v: graph[u]) pq.push({v.second, {v.first, u}});
  }
  return(cost);
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i ++) graph[i].clear();
    int u, v; lli c;
    for (int i = 0; i < m; i ++)
    {
      scanf("%d %d %lld", &u, &v, &c); u --, v --;
      graph[u].push_back({v, c}); graph[v].push_back({u, c});
    }
    lli mstCost = prim();
    printf("%lld\n", mstCost);
  }
  return(0);
}
