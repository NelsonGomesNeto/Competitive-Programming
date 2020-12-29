#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3, maxT = 1e4, maxK = 10;
const int inf = maxN * maxN * maxK + 1;

int n, m, k;
int o, t;
vector<int> graph[maxN];
int orders[maxN];
struct Special
{
  int u, value;
  void read() { scanf("%d %d", &u, &value); u--; }
};
Special specials[maxN];

int dist[maxN][maxN];
void bfs(int origin)
{
  for (int i = 0; i < n; i++) dist[origin][i] = inf;
  queue<int> q; q.push(origin);
  dist[origin][origin] = 0;
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (int v: graph[u])
      if (dist[origin][u] + k < dist[origin][v])
      {
        dist[origin][v] = dist[origin][u] + k;
        q.push(v);
      }
  }
}

int memo[maxN + 1][maxT + 1];
bool visited[maxN + 1][maxT + 1];
int solve(int i = 0, int tl = t)
{
  if (tl < 0) return -inf;
  if (i == o + 1) return 0;
  int &ans = memo[i][tl];
  if (visited[i][tl]) return ans;

  int u = i == 0 ? 0 : orders[i - 1], v = i == n ? 0 : orders[i], s = i ? specials[i - 1].u : -1;
  ans = solve(i + 1, tl - dist[u][v]);
  if (i)
    ans = max(ans, solve(i + 1, tl - (dist[u][s] + dist[s][v])) + specials[i - 1].value);
  visited[i][tl] = true;

  return ans;
}

int main()
{
  while (~scanf("%d %d %d", &n, &m, &k))
  {
    for (int i = 0; i < m; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      graph[u].push_back(v), graph[v].push_back(u);
    }

    scanf("%d %d", &o, &t);
    for (int i = 0; i < o; i++)
    {
      scanf("%d", &orders[i]);
      orders[i]--;
    }
    for (int i = 0; i < o; i++)
      specials[i].read();

    for (int i = 0; i < n; i++)
      bfs(i);

    memset(memo, -1, sizeof(memo));
    memset(visited, false, sizeof(visited));
    int ans = solve();
    if (ans < 0) printf("Impossible\n");
    else printf("%d\n", ans);
  }
  return 0;
}