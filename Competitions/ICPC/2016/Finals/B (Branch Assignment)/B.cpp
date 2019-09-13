#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;

const int maxN = 5e3 + 1; int n, b, s, r;
const lli inf = LLONG_MAX;
list<pair<int, lli>> graph[maxN], revGraph[maxN];
lli dist[maxN], revDist[maxN], cost[maxN][maxN];
pair<lli, int> bestOrder[maxN];

void dijkstra(list<pair<int, lli>> g[], lli d[])
{
  int origin = b + 1;
  for (int i = 1; i <= n; i ++) d[i] = inf;
  priority_queue<pair<lli, int>> pq; pq.push({-(d[origin] = 0), origin});
  while (!pq.empty())
  {
    int u = pq.top().second; lli dd = -pq.top().first; pq.pop();
    if (d[u] < dd) continue;
    for (auto &e: g[u])
      if (d[u] + e.second < d[e.first])
        pq.push({-(d[e.first] = d[u] + e.second), e.first});
  }
  DEBUG {
    printf("%d: ", origin);
    for (int i = 1; i <= n; i ++) printf("%lld%c", d[i], i < n ? ' ' : '\n');
  }
}

lli getCost(int i, int j)
{
  return cost[j][j] - cost[i - 1][j] - cost[j][i - 1] + cost[i - 1][i - 1];
}

lli memo[maxN][maxN];
void solve(int i, int lo = 1, int hi = b, int optlo = 1, int opthi = b)
{
  if (lo > hi) return;

  int mid = (lo + hi) >> 1, optj = optlo;
  lli &best = memo[i][mid] = inf, newCost;
  for (int j = optlo, end = min(mid, opthi); j <= end; j ++)
  {
    newCost = memo[i - 1][j] + getCost(j + 1, mid);
    if (newCost <= best)
      best = newCost, optj = j;
  }

  solve(i, lo, mid - 1, optlo, optj);
  solve(i, mid + 1, hi, optj, opthi);
}

int main()
{
  scanf("%d %d %d %d", &n, &b, &s, &r);
  for (int i = 0, u, v, l; i < r; i ++)
  {
    scanf("%d %d %d", &u, &v, &l);
    graph[u].push_back({v, l});
    revGraph[v].push_back({u, l});
  }

  dijkstra(graph, dist);
  dijkstra(revGraph, revDist);

  for (int i = 1; i <= b; i ++)
    bestOrder[i] = {dist[i] + revDist[i], i};
  sort(bestOrder+1, bestOrder+b+1);
  reverse(bestOrder+1, bestOrder+b+1);

  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= n; j ++)
      cost[i][j] = (i == j || bestOrder[i].second == b + 1 || bestOrder[j].second == b + 1 ? 0 : revDist[bestOrder[i].second] + dist[bestOrder[j].second])
                   + cost[i - 1][j] + cost[i][j - 1] - cost[i - 1][j - 1];

  for (int i = 1; i <= n; i ++)
    memo[1][i] = getCost(1, i);
  for (int i = 2; i <= s; i ++)
    solve(i);
  DEBUG printf("%lld %lld\n", memo[s][n], memo[s][b]);
  else printf("%lld\n", memo[s][b]);

  return(0);
}