#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, m, a, b, c;
const int inf = 1e6;
struct Edge { int to, index; };
vector<Edge> graph[maxN];
lli p[maxN];
bool toPay[maxN];

int prv[maxN], prvEdge[maxN];
set<int> bfsPath;
int bfs(int source, int target)
{
  for (int i = 0; i < n; i++) prv[i] = -2;
  queue<int> q; q.push(source), prv[source] = -1;
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (Edge &e: graph[u])
      if (prv[e.to] == -2)
        prv[e.to] = u, prvEdge[e.to] = e.index, q.push(e.to);
  }

  int ans = 0;
  for (int u = target; u != source; u = prv[u])
    toPay[prvEdge[u]] = true, ans++, bfsPath.insert(prvEdge[u]);
  return ans;
}

int dist[maxN];
set<int> dijkstraPath;
int dijkstra(int source, int target)
{
  for (int i = 0; i < n; i++) dist[i] = inf;
  priority_queue<pair<int, int>> pq; pq.push({dist[source] = 0, source});
  while (!pq.empty())
  {
    int u = pq.top().second, d = -pq.top().first; pq.pop();
    if (d > dist[u]) continue;
    for (Edge &e: graph[u])
      if (dist[u] + toPay[e.index] < dist[e.to])
        pq.push({-(dist[e.to] = dist[u] + toPay[e.index]), e.to}), prv[e.to] = u, prvEdge[e.to] = e.index;
  }
  for (int u = target; u != source; u = prv[u])
    dijkstraPath.insert(prvEdge[u]);
  return dist[target];
}

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    bfsPath.clear(), dijkstraPath.clear();
    for (int i = 0; i < n; i++) graph[i].clear();

    scanf("%d %d %d %d %d", &n, &m, &a, &b, &c); a--, b--, c--;
    for (int i = 0; i < m; i++) scanf("%lld", &p[i]);
    for (int i = 0; i < m; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      graph[u].push_back({v, i}), graph[v].push_back({u, i});
      toPay[i] = true;
    }
    sort(p, p+m);

    int used = bfs(a, b);
    DEBUG printf("used: %d\n", used);
    used += dijkstra(b, c);
    DEBUG printf("used: %d\n", used);
    lli ans = 0;
    for (int i = 0; i < used; i++)
      ans += p[i];
    int c = 0;
    for (int i: bfsPath)
      if (dijkstraPath.count(i))
        ans += p[c++];
    printf("%lld\n", ans);
  }
  return 0;
}