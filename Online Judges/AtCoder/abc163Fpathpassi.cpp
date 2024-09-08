#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  What if this problem were DP on Tree?
  And we actually want to calculate how many paths pass through u (for every u)
*/

const int maxN = 2e5; int n;
int colors[maxN]; lli ans[maxN];
int colorCnt[maxN];
vector<int> tree[maxN];

int subtreeSize[maxN];
void dfs1(int u = 0, int prv = -1)
{
  subtreeSize[u] = 1;
  for (int v: tree[u])
    if (v != prv)
    {
      dfs1(v, u);
      subtreeSize[u] += subtreeSize[v];
    }
}

lli toAdd(int branchSize)
{
  return 2LL*branchSize + (lli)branchSize*(n - branchSize - 1);
}
int colorSubtree[maxN]; int hadAbove[maxN];
void dfs2(int u = 0, int prv = -1)
{
  ans[colors[u]] += 2; // path with only u (times 2 because we will divide by 2 later)

  if (prv != -1) // parent as a child
    ans[colors[u]] += toAdd(n - subtreeSize[u]);

  int beforeAll = colorSubtree[colors[u]];

  hadAbove[colors[u]]++;

  for (int v: tree[u])
    if (v != prv)
    {
      // if (hadAbove[colors[v]] == 0)
      // ans[colors[v]] -= 2LL * colorSubtree[colors[v]] * subtreeSize[v];
      DEBUG printf("left %d | %d - %d = %lld\n", colors[v] + 1, u + 1, v + 1, 2LL * colorSubtree[colors[v]] * subtreeSize[v]);

      int before = colorSubtree[colors[u]], bf = colorSubtree[colors[v]];
      hadAbove[colors[v]]--;
      dfs2(v, u);
      int after = colorSubtree[colors[u]], af = colorSubtree[colors[v]];

      ans[colors[u]] += toAdd(subtreeSize[v]);

      ans[colors[u]] -= 2LL * (after - before) * (n - subtreeSize[v] - before); // but you still need to count the ones the have passed before you (not only below)
      DEBUG printf("down %d | %d - %d = %lld\n", colors[v] + 1, u + 1, v + 1, 2LL * (after - before) * (n - subtreeSize[v] - before));
      // if (bf) ans[colors[v]] -= (af - bf) * subtreeSize[v] >> 1LL;
      // ans[colors[v]] -= 2LL * (subtreeSize[v] - (af - bf) + 1) * (bf);
    }
  ans[colors[u]] -= 2LL * beforeAll * subtreeSize[u];

  colorSubtree[colors[u]] = beforeAll + subtreeSize[u];
}

int main()
{
  int t = 0;
  while (scanf("%d", &n) != EOF)
  {
    if (t++) printf("----------------------\n");
    for (int i = 0; i < n; i++) tree[i].clear(), ans[i] = 0, colorSubtree[i] = 0, hadAbove[i] = 0;

    for (int i = 0; i < n; i++)
    {
      scanf("%d", &colors[i]);
      colors[i]--;
      colorCnt[colors[i]]++;
    }

    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
    }

    dfs1();
    dfs2();

    for (int i = 0; i < n; i++)
      printf("%lld\n", ans[i] >> 1LL);
  }
  return 0;
}