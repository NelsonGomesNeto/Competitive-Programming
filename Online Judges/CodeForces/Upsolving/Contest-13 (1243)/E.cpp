#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, m, a, b, c;
const lli inf = 1e16;
struct Edge { int to, index; };
vector<Edge> graph[maxN];
lli p[maxN];
lli toPay[maxN];

int prv[maxN], prvEdge[maxN];
set<int> bfsPath;
int dd[2][maxN];
int bfs(int source, int target)
{
  for (int i = 0; i < n; i++) prv[i] = -2, dd[0][i] = dd[1][i] = 1e6;
  priority_queue<pair<int, pair<int, int>>> q; q.push({dd[0][source] = 0, {false, source}}), prv[source] = -1;
  dd[1][source] = 0;
  while (!q.empty())
  {
    int u = q.top().second.second, had = q.top().second.first, d = -q.top().first; q.pop();
    printf("%d %d %d\n", u, had, d);
    if (d > dd[had][u]) continue;
    for (Edge &e: graph[u])
    {
      printf("\t%d %d\n", e.to, had || (e.to == c));
      if (dd[had][u] + (e.to != c) < dd[had || (e.to == c)][e.to])
        prv[e.to] = u, prvEdge[e.to] = e.index, q.push({-(dd[had || (e.to == c)][e.to] = dd[had][u] + (e.to != c)), {had || (e.to == c), e.to}});
    }
  }

  int ans = 0;
  for (int u = target; u != source; u = prv[u])
    toPay[prvEdge[u]] = p[ans++];
  return ans;
}

map<int, lli> dist[maxN];
set<int> dijkstraPath;
lli dijkstra(int used, int source, int target)
{
  for (int i = 0; i < n; i++) dist[i].clear(), prv[i] = -1;
  priority_queue<pair<lli, pair<int, int>>> pq; pq.push({dist[source][used] = 0, {source, used}});
  while (!pq.empty())
  {
    int u = pq.top().second.first, cur = pq.top().second.second; lli d = -pq.top().first; pq.pop();
    DEBUG printf("\t%d %d %lld\n", u + 1, cur, d);
    if (d > dist[u][cur]) continue;
    for (Edge &e: graph[u])
    {
      if (toPay[e.index] == -1 && cur >= m) continue;
      lli newCost = dist[u][cur] + (toPay[e.index] == -1 ? p[cur] : toPay[e.index]);
      int newCur = cur + (toPay[e.index] == -1);
      DEBUG printf("\t\t%d %lld - %d\n", e.to + 1, newCost, newCur);
      if (!dist[e.to].count(newCur) || newCost < dist[e.to][newCur])
        pq.push({-(dist[e.to][newCur] = newCost), {e.to, newCur}}), prv[e.to] = u, prvEdge[e.to] = e.index;
    }
  }
  lli ans = inf;
  for (auto i: dist[target])
    ans = min(ans, i.second);
  return ans;
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
      toPay[i] = -1;
    }
    sort(p, p+m);

    int used = bfs(a, b);
    lli ans = 0;
    for (int i = 0; i < used; i++)
      ans += p[i];
    ans += dijkstra(used, b, c);
    // int c = 0;
    // for (int i: bfsPath)
    //   if (dijkstraPath.count(i))
    //     ans += p[c++];
    printf("%lld\n", ans);
  }
  return 0;
}
