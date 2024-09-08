#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, m;
const int inf = 1e9;
const lli mod = 1e9 + 7;
vector<int> graph[maxN];

int dist[maxN];
int bfs()
{
  for (int i = 0; i < n; i++) dist[i] = inf;
  queue<pair<int, int>> q;
  q.push(make_pair(0, -1)); dist[0] = 0;
  while (!q.empty())
  {
    int u = q.front().first, prv = q.front().second; q.pop();
    for (int v: graph[u])
      if (v != prv && dist[v] == inf)
      {
        dist[v] = dist[u] + 1;
        q.push(make_pair(v, u));
      }
  }
  return dist[n - 1];
}

unordered_map<int, lli> memo[maxN];
lli dfs(int u = 0, int prv = -1, int d = 0)
{
  if (dist[u] < d) return 0;
  if (u == n - 1) return 1;
  if (memo[u].count(prv)) return memo[u][prv];

  lli &ans = memo[u][prv];
  for (int v: graph[u])
    if (v != prv)
      ans = (ans + dfs(v, u, d + 1)) % mod;
  return ans;
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; i++) graph[i].clear();
    for (int i = 0; i < m; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      graph[u].push_back(v), graph[v].push_back(u);
    }

    int minDist = bfs();
    for (int i = 0; i < n; i++) memo[i].clear();
    lli ans = dfs();
    printf("%lld\n", ans);
  }
  return 0;
}