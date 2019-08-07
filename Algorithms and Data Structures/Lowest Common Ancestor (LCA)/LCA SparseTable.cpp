#include <bits/stdc++.h>
using namespace std;
vector<int> eulerianTour;
const int maxN = 1e6, maxLog = floor(log2(2e6)) + 1;
vector<int> tree[maxN];
int uMap[maxN], revMap[2*maxN], first[maxN], now;
int sparseTable[2*maxN][maxLog], logdp[2*maxN + 1];
// The distance between two vertices is very straight forward:
// first find the level of each node
// distance(u, v) = (level[u] - level[LCA(u, v)]) + (level[v] - level[LCA(u, v)])
// distance(u, v) = level[u] + level[u] - 2*level[LCA(u, v)]

void dfs(int u)
{
  revMap[now] = u; uMap[u] = now ++;
  first[u] = eulerianTour.size();
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

void printSpacing(int depth)
{
  for (int i = 0; i < depth; i ++) printf("   ");
}

void printTree(int u, int depth)
{
  printSpacing(depth);
  printf("%d\n", u);
  for (auto v: tree[u])
    printTree(v, depth + 1);
}

int LCA(int u, int v)
{
  int ans = 1 << 20, lo = min(first[u], first[v]), hi = max(first[u], first[v]);
  int qs = logdp[hi - lo + 1];
  return(revMap[min(sparseTable[lo][qs], sparseTable[hi - (1 << qs) + 1][qs])]);
  for (int j = maxLog; j >= 0; j --)
    if (lo + (1 << j) - 1 <= hi)
    {
      ans = min(ans, sparseTable[lo][j]);
      lo += (1 << j);
    }
  return(revMap[ans]);
}

int LCANaive(int u, int v)
{
  int ans = 1 << 20, lo = min(first[u], first[v]), hi = max(first[u], first[v]);
  while (lo <= hi)
  {
    ans = min(ans, eulerianTour[lo]);
    lo ++;
  }
  return(revMap[ans]);
}

int main()
{
  logdp[1] = 0; for (int i = 2; i <= maxN; i ++) logdp[i] = logdp[i >> 1] + 1;
  int n, u, v; scanf("%d", &n);
  for (int i = 0; i < n - 1; i ++)
  {
    scanf("%d %d", &u, &v);
    tree[u].push_back(v);
  }
  build();
  printTree(0, 0);

  for (int i = 0; i < eulerianTour.size(); i ++)
    printf("%d%c", eulerianTour[i], i < eulerianTour.size() - 1 ? ' ' : '\n');
  for (int i = 0; i < n; i ++)
    printf("(%d -> %d, %d)%c", i, uMap[i], first[uMap[i]], i < n - 1 ? ' ' : '\n');

  while (scanf("%d %d", &u, &v) != EOF)
  {
    printf("LCA(%d, %d) = %d | %s\n", u, v, LCA(u, v), LCA(u, v) == LCANaive(u, v) ? "true" : "false");
  }

  return(0);
}
