#include <bits/stdc++.h>
using namespace std;
#define lli long long int
const int maxN = 1e5;
vector<pair<int, lli>> tree[maxN];
int now, first[maxN], uMap[maxN], revMap[2*maxN]; lli dist[maxN]; vector<int> eulerianTour;
int sparseTable[2*maxN][(int) floor(log2(2*maxN)) + 1], logDP[2*maxN + 1];

void printSpacing(int depth) { while (depth --) printf("   "); }

void dfs(int u, lli d, int depth)
{
  // printSpacing(depth); printf("(%d, %lld)\n", u, d);
  revMap[now] = u; uMap[u] = now ++; dist[u] = d;
  first[u] = eulerianTour.size();
  eulerianTour.push_back(uMap[u]);
  for (auto v: tree[u])
  {
    dfs(v.first, d + v.second, depth + 1);
    eulerianTour.push_back(uMap[u]);
  }
}

void build()
{
  now = 0; dfs(0, 0, 0); int logn = floor(log2(eulerianTour.size())) + 1;
  for (int i = 0; i < eulerianTour.size(); i ++) sparseTable[i][0] = eulerianTour[i];
  for (int j = 1; j <= logn; j ++)
    for (int i = 0, shift = (1 << (j - 1)); i + shift < eulerianTour.size(); i ++)
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
  int n;
  while (scanf("%d", &n) && n)
  {
    int u; lli d; for (int i = 0; i < n; i ++) tree[i].clear();
    for (int i = 1; i < n; i ++)
    {
      scanf("%d %lld\n", &u, &d);
      tree[u].push_back({i, d});
    }
    eulerianTour.clear(); build();

    int q; scanf("%d", &q);
    for (int i = 0, u, v; i < q; i ++)
    {
      scanf("%d %d", &u, &v);
      int lca = LCA(u, v);
      // printf("LCA(%d, %d) = %d; dist = %lld\n", u, v, lca, dist[u] + dist[v] - 2*dist[lca]);
      printf("%lld%c", dist[u] + dist[v] - 2*dist[lca], i < q - 1 ? ' ' : '\n');
    }
  }
  return(0);
}
