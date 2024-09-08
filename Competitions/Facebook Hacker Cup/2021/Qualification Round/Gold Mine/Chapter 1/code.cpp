#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50; int n, k;
lli c[maxN];
vector<int> tree[maxN];
int edgeMap[maxN][maxN];
lli allUsed, allBlocked;

lli dist[maxN][maxN + 1];
struct Node
{
  int u, jumps; lli d;
  lli blocked, used;
  bool operator<(const Node &other) const { return d < other.d; }
};
lli dijkstra()
{
  for (int i = 0; i < n; i++) fill(dist[i], dist[i]+n+1, -1);
  priority_queue<Node> pq;
  pq.push(Node{0, 0, dist[0][0] = c[0], 0, 1});
  lli ans = 0;
  while (!pq.empty())
  {
    Node now = pq.top(); pq.pop();
    DEBUG printf("\t%d %d %lld | %lld %lld\n", now.u, now.jumps, now.d, now.blocked, now.used);
    if (now.u == 0) ans = max(ans, now.d);
    if (now.u == 0 && (now.used == allUsed || now.blocked == allBlocked)) break;
    // if (now.d < dist[now.u][now.jumps]) continue;

    for (int v = 0; v < n; v++)
    {
      if (edgeMap[now.u][v] != -1)
      {
        if (!(now.blocked & (1LL << edgeMap[now.u][v]))) // && now.d + ((~now.used >> v) & 1LL) * c[v] > dist[v][now.jumps])
        {
          dist[v][now.jumps] = now.d + ((~now.used >> v) & 1LL) * c[v];
          Node nxt = now;
          nxt.u = v, nxt.d = dist[v][now.jumps];
          nxt.blocked |= 1LL << edgeMap[now.u][v];
          nxt.used |= 1LL << v;
          pq.push(nxt);
        }
      }

      if (now.jumps < k)
      {
        // if (now.d + ((~now.used >> v) & 1LL) * c[v] >= dist[v][now.jumps + 1])
        {
          dist[v][now.jumps + 1] = now.d + ((~now.used >> v) & 1LL) * c[v];
          Node nxt = now;
          nxt.u = v, nxt.d = dist[v][now.jumps + 1];
          nxt.used |= 1LL << v;
          nxt.jumps += 1;
          pq.push(nxt);
        }
      }
    }
  }
  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    // scanf("%d %d", &n, &k);
    scanf("%d", &n); k = 1;

    allUsed = (1LL << n) - 1, allBlocked = (1LL << (n - 1)) - 1;

    for (int i = 0; i < n; i++) scanf("%lld", &c[i]);
    for (int i = 0; i < n; i++) tree[i].clear(), fill(edgeMap[i], edgeMap[i]+n, -1);
    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
      edgeMap[u][v] = edgeMap[v][u] = i - 1;
    }

    lli ans = dijkstra();
    printf("Case #%d: %lld\n", tt, ans);
  }
  return 0;
}