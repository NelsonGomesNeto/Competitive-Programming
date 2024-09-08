#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, m;
const int inf = 2*maxN;
vector<int> tree[maxN];

int d[maxN];
void bfs()
{
  for (int i = 0; i < n; i++) d[i] = inf;
  queue<int> q;
  q.push(0), d[0] = 0;
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (int v: tree[u])
      if (d[u] + 1 < d[v])
        q.push(v), d[v] = d[u] + 1;
  }
}

int memo[maxN][2];
int dfs(int u, bool done = false)
{
  int &ans = memo[u][done];
  if (ans != -1) return ans;

  ans = d[u];
  for (int v: tree[u])
    if (d[u] < d[v])
      ans = min(ans, dfs(v, done));
    else if (d[u] >= d[v] && !done)
      ans = min(ans, dfs(v, true));
  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) tree[i].clear();
    for (int i = 0; i < m; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v);

    }

    bfs();
    memset(memo, -1, sizeof(memo));
    for (int i = 0; i < n; i++)
      dfs(i);
    for (int i = 0; i < n; i++)
      printf("%d%c", memo[i][0], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}