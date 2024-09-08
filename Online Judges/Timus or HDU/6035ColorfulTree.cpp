#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
const int root = 0;
int colors[maxN];
vector<int> tree[maxN];

lli subtreeSize[maxN];
lli subtreeWithDifferentColorSize[maxN], colorCount[maxN];
void dfs1(int u = root, int prv = -1)
{
  lli before = colorCount[colors[u]];
  subtreeSize[u] = 1;
  subtreeWithDifferentColorSize[u] = 0;
  for (int v: tree[u])
    if (v != prv)
    {
      dfs1(v, u);
      subtreeSize[u] += subtreeSize[v];
      subtreeWithDifferentColorSize[u] += subtreeWithDifferentColorSize[v];
    }
  subtreeWithDifferentColorSize[u] += colorCount[colors[u]] == before;
  colorCount[colors[u]]++;
}

/*
  I want to calculate the sum of depths for each node.
  Then it will be that / 2;
*/

lli depthSum[maxN], depthSum2[maxN];
void dfs2(int u = root, int prv = -1)
{
  depthSum[u] = 1;
  for (int v: tree[u])
    if (v != prv)
    {
      dfs2(v, u);
      depthSum[u] += depthSum[v] + subtreeSize[v];
      // subtract from subtreeSize[v] the amount of guys with the same color
    }
}

// depthSum for each node through re-rooting
lli totalDepthSum[maxN], totalDepthSum2[maxN];
void dfs3(int u = root, int prv = -1)
{
  totalDepthSum[u] += depthSum[u];
  for (int v: tree[u])
    if (v != prv)
    {
      totalDepthSum[v] += totalDepthSum[u] + (n - subtreeSize[v]) - (depthSum[v] + subtreeSize[v]);
      dfs3(v, u);
    }
}

lli toRemove[maxN];

/*
  For each node:
    set as root
    calculate the number of paths that will have at least another node with the same color as root
    that's what you need to remove --' (of this node)
  sum them :)

  below we're already handling everything below u
  now we need to handle the other branch (above (will be down when it become root))
*/

lli colorBelowSum[maxN], nodeBelowSum[maxN];
vector<lli> branchDelta[maxN];
void dfs4(int u = root, int prv = -1)
{
  lli before = colorBelowSum[colors[u]];
  for (int v: tree[u])
    if (v != prv)
    {
      lli beforeV = colorBelowSum[colors[u]];
      dfs4(v, u);
      nodeBelowSum[u] += colorBelowSum[colors[u]] - beforeV;
      toRemove[u] += (lli)(n - subtreeSize[v]) * (colorBelowSum[colors[u]] - beforeV);
      branchDelta[u].push_back(colorBelowSum[colors[u]] - beforeV);
    }
    else
      branchDelta[u].push_back(0);
  colorBelowSum[colors[u]] = before + subtreeSize[u];
}

lli aboveToAdd[maxN], belowToRemove[maxN];
void dfs5(int u = root, int prv = -1)
{
  DEBUG printf("\t%d(%d) %lld %lld\n", u + 1, colors[u] + 1, aboveToAdd[colors[u]], belowToRemove[colors[u]]);
  if (aboveToAdd[colors[u]] != -1)
    toRemove[u] += subtreeSize[u] * (aboveToAdd[colors[u]] + 0*subtreeSize[u]);
  if (belowToRemove[colors[u]] != -1)
    toRemove[u] -= subtreeSize[u] * (belowToRemove[colors[u]]);
  for (int i = 0; i < tree[u].size(); i++)
  {
    int v = tree[u][i]; lli bdelta = branchDelta[u][i];
    if (v != prv)
    {
      lli belowBefore = belowToRemove[colors[u]], aboveBefore = aboveToAdd[colors[u]];
      belowToRemove[colors[u]] = colorBelowSum[colors[u]] - nodeBelowSum[u];
      aboveToAdd[colors[u]] = (n - subtreeSize[v] - (nodeBelowSum[u] - bdelta));
      dfs5(v, u);
      belowToRemove[colors[u]] = belowBefore;
      aboveToAdd[colors[u]] = aboveBefore;
    }
  }
}

int cnt[maxN];
lli qq(int u, int prv = -1, int sum = 0)
{
  sum += cnt[colors[u]] == 0;
  lli res = sum;
  cnt[colors[u]]++;
  for (int v: tree[u])
    if (v != prv)
      res += qq(v, u, sum);
  cnt[colors[u]]--;
  return res;
}

int main()
{
  int t = 1;
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &colors[i]), tree[i].clear(), branchDelta[i].clear();
      colors[i]--;
      depthSum[i] = depthSum2[i] = totalDepthSum[i] = 0;
      subtreeWithDifferentColorSize[i] = colorCount[i] = 0;
      colorBelowSum[i] = nodeBelowSum[i] = 0;
      aboveToAdd[i] = belowToRemove[i] = 0;
      toRemove[i] = 0;
    }

    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
    }

    lli lol = -n;
    DEBUG
      for (int i = 0; i < n; i++)
      {
        memset(cnt, 0, sizeof(cnt));
        lol += qq(i);
      }

    dfs1();
    dfs2();
    dfs3();
    dfs4();
    for (int i = 0; i < n; i++)
    {
      toRemove[i] += (colorBelowSum[colors[i]] - subtreeSize[i]) * subtreeSize[i];
      belowToRemove[colors[i]] = aboveToAdd[colors[i]] = -1;
    }
    dfs5();

    // ans = sum[root];
    lli ans = 0, removed = n;
    for (int i = 0; i < n; i++)
    {
      DEBUG printf("%d(%d) (%lld %lld) || %lld %lld || %lld || %lld\n",
      i + 1, colors[i] + 1,
      subtreeSize[i], nodeBelowSum[i],
      depthSum[i], totalDepthSum[i],
      colorBelowSum[i],
      toRemove[i]);

      ans += totalDepthSum[i];
      removed += toRemove[i];
    }

    DEBUG printf("Case #%d: %lld %lld (%lld)\n", t, ans >> 1LL, (ans - removed) >> 1LL, lol >> 1LL);
    printf("Case #%d: %lld\n", t++, (ans - removed) >> 1LL);
    DEBUG if ((ans - removed) >> 1LL != lol >> 1LL) printf("NOT OK!\n");
  }
  return 0;
}