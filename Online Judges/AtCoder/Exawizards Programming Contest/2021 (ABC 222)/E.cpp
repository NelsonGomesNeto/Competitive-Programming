#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli mod = 998244353;
const int maxN = 1e3, maxM = 1e2; int n, m, k;
int a[maxM];
int edgeCnt[maxN - 1];
int edgeMap[maxN][maxN];
vector<int> tree[maxN];

int level[maxN], parent[maxN];
void dfs(int u = 0, int prv = -1)
{
  for (int v: tree[u])
    if (v != prv)
    {
      level[v] = level[u] + 1;
      parent[v] = u;
      dfs(v, u);
    }
}

unordered_map<lli, lli> memo[maxN - 1];
lli solve(int i = 0, int r = 0, int b = 0)
{
  int rb = r - b;
  if (i == n - 1) return rb == k;
  if (memo[i].count(rb)) return memo[i][rb];
  lli &ans = memo[i][rb];

  ans = (solve(i + 1, r + edgeCnt[i], b)
      +  solve(i + 1, r, b + edgeCnt[i])) % mod;

  return ans;
}

int main()
{
  while (~scanf("%d %d %d", &n, &m, &k))
  {
    for (int i = 0; i < m; i++)
    {
      scanf("%d", &a[i]);
      a[i]--;
    }

    for (int i = 0; i < n; i++) tree[i].clear();
    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
      edgeMap[u][v] = edgeMap[v][u] = i - 1;
    }

    dfs();

    memset(edgeCnt, 0, sizeof(edgeCnt));
    for (int i = 1; i < m; i++)
    {
      int u = a[i - 1], v = a[i];

      while (u != v)
      {
        if (level[u] < level[v]) swap(u, v);

        edgeCnt[edgeMap[u][parent[u]]]++;
        u = parent[u];
      }
    }

    for (int i = 0; i < n - 1; i++) memo[i].clear();
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}