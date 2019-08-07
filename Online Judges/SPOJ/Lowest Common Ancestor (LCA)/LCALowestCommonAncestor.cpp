#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e3, maxLog = floor(log2(2e3)) + 1, maxEP = 2e3;
vector<int> tree[maxN];
int sparseTable[maxEP][maxLog], logDP[maxEP + 1];
vector<int> eulerianTour;
int uMap[maxEP], revMap[maxEP], first[maxEP], now;

void dfs(int u)
{
  revMap[now] = u; uMap[u] = now ++;
  first[uMap[u]] = eulerianTour.size();
  eulerianTour.push_back(uMap[u]);
  for (auto v: tree[u])
  {
    dfs(v);
    eulerianTour.push_back(uMap[u]);
  }
}

void build()
{
  now = 0; dfs(0);
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
  logDP[1] = 0; for (int i = 2; i <= maxEP; i ++) logDP[i] = logDP[i >> 1] + 1;

  int t; scanf("%d", &t);
  for (int tt = 0; tt < t; tt ++)
  {
    eulerianTour.clear();
    int n; scanf("%d", &n);
    for (int i = 0, m; i < n; i ++)
    {
      tree[i].clear();
      scanf("%d", &m);
      for (int j = 0, u; j < m; j ++)
      {
        scanf("%d", &u);
        tree[i].push_back(u - 1);
      }
    }
    build();

    printf("Case %d:\n", tt + 1);
    int q; scanf("%d", &q);
    while (q --)
    {
      int u, v; scanf("%d %d", &u, &v); u --, v --;
      printf("%d\n", LCA(uMap[u], uMap[v]) + 1);
    }
  }
  return(0);
}
