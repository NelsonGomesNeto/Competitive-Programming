#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  Use Dijkstra to calculate the shortest distance from s to every other city
  Counting cities with missiles:
    for u in cities:
      if (dist[u] == L):
        there's missile in the u-th city
  Counting roads with missiles:
    for (u, v) in roads:
      if (dist[u] < l and dist[u] + w(u, v) > L and w(u, v) > (L - dist[u]) + (L - dist[v])):
        there're two missiles in the road (u, v)
          at (L - dist[u]) from u to v
          at (L - dist[v]) from v to u
      if (dist[u] < l and dist[u] + w(u, v) > L and w(u, v) == (L - dist[u]) + (L - dist[v])):
        there's a missile in the road (u, v)
          at (L - dist[u]) from u to v (exactly in the middle of this road)
    Observation:
      The position of the missile MUST be in the shortest path from s. So even if
      dist[u] < L and dist[u] + w(u, v) > L is true; you might be able to reach the
      same position on the road if you've started from v instead.
*/

const int maxN = 1e5, inf = 2e8 + 10; int n, m, s, l;
vector<pair<int, int>> graph[maxN];

int dist[maxN], prv[maxN];
void dijkstra()
{
  for (int i = 0; i < n; i ++) dist[i] = inf;
  priority_queue<pair<int, int>> pq; pq.push({-(dist[s] = 0), s});
  while (!pq.empty())
  {
    int u = pq.top().second, d = -pq.top().first; pq.pop();
    if (d > dist[u]) continue;
    for (auto &e: graph[u])
      if (dist[u] + e.second < dist[e.first])
        pq.push({-(dist[e.first] = dist[u] + e.second), e.first}), prv[e.first] = u;
  }
}

int main()
{
  while (scanf("%d %d %d", &n, &m, &s) != EOF)
  {
    s --;
    for (int i = 0; i < n; i ++) graph[i].clear();
    for (int i = 0; i < m; i ++)
    {
      int u, v, w; scanf("%d %d %d", &u, &v, &w); u --, v --;
      graph[u].push_back({v, w}), graph[v].push_back({u, w});
    }
    scanf("%d", &l);

    dijkstra();
    int ans = 0;
    for (int i = 0; i < n; i ++)
    {
      if (dist[i] == l)
        ans ++;
      if (dist[i] < l)
        for (auto &e: graph[i])
          if (dist[i] + e.second > l && (e.second > (l - dist[i]) + (l - dist[e.first]) || (e.second == (l - dist[i]) + (l - dist[e.first]) && i < e.first)))
            ans ++;
    }
    printf("%d\n", ans);
  }

  return 0;
}