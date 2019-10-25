#include <bits/stdc++.h>
using namespace std;

const int maxN = 5000;

vector<int> tree[5000], parent[5000], eulerianTour;
int uMap[maxN], revMap[2*maxN], first[maxN], now;
int sparseTable[2*maxN][(int) floor(log2(2*maxN)) + 1], logDP[2*maxN + 1];
int visited[maxN], level[maxN];

void dfs(int u, int depth, deque<int> nowParent)
{
  nowParent.push_back(u);
  for (auto i: nowParent) parent[u].push_back(i);
  reverse(parent[u].begin(), parent[u].end());

  visited[u] = 1; level[u] = depth;
  revMap[now] = u; uMap[u] = now ++;
  first[u] = eulerianTour.size();
  eulerianTour.push_back(uMap[u]);
  for (auto v: tree[u])
    if (!visited[v])
    {
      dfs(v, depth + 1, nowParent);
      eulerianTour.push_back(uMap[u]);
    }

  nowParent.pop_front();
}

void build()
{
  eulerianTour.clear(); memset(visited, 0, sizeof(visited)); deque<int> nowParent;
  now = 0; dfs(0, 0, nowParent);
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
  int n;
  while (scanf("%d", &n) && n)
  {
    for (int i = 0; i < n; i ++) tree[i].clear(), parent[i].clear();
    int u, v;
    for (int i = 0; i < n - 1; i ++)
    {
      scanf("%d %d", &u, &v); u --, v --;
      tree[u].push_back(v);
      tree[v].push_back(u);
    }
    build();

    int q; scanf("%d", &q);
    while (q --)
    {
      scanf("%d %d", &u, &v); u --, v --;
      int lca = LCA(u, v); int distance = level[u] + level[v] - 2*level[lca];
      if (level[u] > level[v]) { int aux = u; u = v; v = aux; }
      // printf("%d LCA(%d, %d) = %d, dist = %d\n", n, u + 1, v + 1, lca + 1, distance);
      int pos = (distance >> 1);
      if (distance & 1)
        printf("The fleas jump forever between %d and %d.\n", min(parent[v][pos], parent[v][pos + 1]) + 1, max(parent[v][pos], parent[v][pos + 1]) + 1);
      else printf("The fleas meet at %d.\n", parent[v][pos] + 1);
    }
  }
  return(0);
}
