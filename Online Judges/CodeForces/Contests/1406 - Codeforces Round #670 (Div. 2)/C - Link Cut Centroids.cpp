#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
vector<int> tree[maxN];

int parent[maxN];
int subtreeSize[maxN], level[maxN];
void calc(int u = 0, int prv = -1)
{
  subtreeSize[u] = 1;
  for (int v: tree[u])
    if (v != prv)
    {
      level[v] = level[u] + 1, parent[v] = u;
      calc(v, u);
      subtreeSize[u] += subtreeSize[v];
    }
}

int cutPoint = n;
vector<int> centroids;
void dfs(int u = 0, int prv = -1)
{
  int biggestSubtree = 0;
  if (prv != -1) biggestSubtree = n - subtreeSize[u];
  for (int v: tree[u])
    if (v != prv)
    {
      biggestSubtree = max(biggestSubtree, subtreeSize[v]);
      dfs(v, u);
    }
  if (biggestSubtree < cutPoint)
    cutPoint = biggestSubtree, centroids.clear();
  if (biggestSubtree == cutPoint)
    centroids.push_back(u);
}

int aLeaf;
void getLeafSub(int u, int prv)
{
  if (tree[u].size() == 1) aLeaf = u;
  for (int v: tree[u])
    if (v != prv)
      getLeafSub(v, u);
}
int bLeaf;
void getLeafSubAvoid(int u, int avoid, int prv = -1)
{
  if (tree[u].size() == 1) bLeaf = u;
  for (int v: tree[u])
    if (v != prv && v != avoid)
      getLeafSubAvoid(v, avoid, u);
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    for (int i = 0; i < n; i++) tree[i].clear();
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
    }

    memset(level, 0, sizeof(level));
    calc();
    centroids.clear(), cutPoint = n;
    dfs();
    if (centroids.size() == 1)
    {
      printf("%d %d\n", 1, tree[0][0] + 1);
      printf("%d %d\n", 1, tree[0][0] + 1);
    }
    else
    {
      int a = centroids[0], b = centroids[1];
      if (level[a] < level[b]) swap(a, b);
      aLeaf = -1;
      // for (int v: tree[a])
      //   if (v != b)
      //     aLeaf = v;
      getLeafSub(a, b);
      bLeaf = -1;
      for (int v: tree[b])
        if (v != a)
          bLeaf = v;
      // getLeafSubAvoid(b, a);
      assert(aLeaf != -1 && bLeaf != -1);

      // printf("%d %d | %d %d\n", a + 1, b + 1, aLeaf + 1, bLeaf + 1);

      printf("%d %d\n", aLeaf + 1, parent[aLeaf] + 1);
      printf("%d %d\n", b + 1, aLeaf + 1);
    }
  }
  return 0;
}
