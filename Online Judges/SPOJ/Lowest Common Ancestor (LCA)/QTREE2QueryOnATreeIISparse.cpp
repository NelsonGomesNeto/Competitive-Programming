#include <bits/stdc++.h>
using namespace std;
#define lli long long int
const int maxN = 1e4, maxLog = floor(log2(2e4)) + 1;
vector<pair<int, int>> tree[maxN];
int parent[maxN]; lli cost[maxN];

vector<int> eulerianTour;
int first[maxN], uMap[maxN], revMap[2*maxN], level[maxN], now;
void dfs(int u, int prev, lli d, int depth)
{
  parent[u] = prev, cost[u] = d, level[u] = depth;
  first[u] = eulerianTour.size(); revMap[now] = u; uMap[u] = now ++;
  eulerianTour.push_back(uMap[u]);
  for (auto v: tree[u])
    if (v.first != prev)
    {
      dfs(v.first, u, d + v.second, depth + 1);
      eulerianTour.push_back(uMap[u]);
    }
}

int sparseTable[2*maxN][maxLog], logDP[2*maxN + 1];
void build()
{
  now = 0; eulerianTour.clear(); dfs(0, -1, 0, 0);
  int n = eulerianTour.size(), logn = floor(log2(eulerianTour.size())) + 1;
  for (int i = 0; i < n; i ++) sparseTable[i][0] = eulerianTour[i];
  for (int j = 1; j <= logn; j ++)
    for (int i = 0, shift = (1 << (j - 1)); i + shift < n; i ++)
      sparseTable[i][j] = min(sparseTable[i][j - 1], sparseTable[i + shift][j - 1]);
}
int LCA(int u, int v)
{
  int lo = min(first[u], first[v]), hi = max(first[u], first[v]);
  int qs = logDP[hi - lo + 1];
  return(revMap[min(sparseTable[lo][qs], sparseTable[hi - (1 << qs) + 1][qs])]);
}

int main()
{
  logDP[1] = 0; for (int i = 2; i <= 2*maxN; i ++) logDP[i] = logDP[i >> 1] + 1;
  int t; scanf("%d", &t);
  while (t --)
  {
    int n; scanf("%d", &n);
    int u, v, c; for (int i = 0; i < n; i ++) tree[i].clear();
    for (int i = 0; i < n - 1; i ++)
    {
      scanf("%d %d %d", &u, &v, &c); u --, v --;
      tree[u].push_back({v, c}); tree[v].push_back({u, c});
    }
    build();

    char op[4 + 1]; int k;
    while (scanf("\n%s", op) && strcmp(op, "DONE"))
    {
      scanf("%d %d", &u, &v); u --, v --;
      int lca = LCA(u, v);
      if (!strcmp(op, "DIST"))
        printf("%lld\n", cost[u] + cost[v] - 2*cost[lca]);
      else
      {
        scanf("%d", &k); k --;
        if (k >= level[u] - level[lca])
        {
          k = (level[v] - level[lca]) - (k - (level[u] - level[lca]));
          u = v;
        }
        while (k --) u = parent[u];
        printf("%d\n", u + 1);
      }
    }
  }
  return(0);
}
