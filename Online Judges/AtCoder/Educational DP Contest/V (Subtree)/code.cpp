#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n; lli m;
vector<int> tree[maxN];

lli res[maxN];
lli onlyBlack[maxN];
vector<lli> multPref[maxN], multSuff[maxN];
lli dfs(int u = 0, int prv = -1)
{
  lli ans = 1;

  vector<lli> mults(tree[u].size(), 1);
  for (int i = 0; i < tree[u].size(); i++)
  {
    int v = tree[u][i];
    if (v != prv)
    {
      mults[i] = dfs(v, u);
      ans = (ans * mults[i]) % m;
    }
  }

  for (int i = 0; i < tree[u].size(); i++)
    multPref[u][i + 1] = multPref[u][i] * mults[i] % m;
  for (int i = tree[u].size() - 1; i >= 0; i--)
    multSuff[u][i] = multSuff[u][i + 1] * mults[i] % m;

  onlyBlack[u] = ans;
  ans = (ans + 1) % m;
  res[u] = ans;
  return ans;
}

void dfs2(int u = 0, int prv = -1, int pos = -1)
{
  if (prv != -1)
  {
    int parentPos = 0;
    while (tree[u][parentPos] != prv) parentPos++;

    // lli parentDfs = dfs(prv, u, false);
    // lli parentDfs = (onlyBlack[prv] / (onlyBlack[u] + 1) % m + 1) % m;
    lli parentDfs = (multPref[prv][pos] * multSuff[prv][pos + 1] % m + 1) % m;
    res[u] = (onlyBlack[u] * parentDfs % m + 1) % m;

    onlyBlack[u] = (res[u] - 1 + m) % m;

    // update multPref and multSuff
    // multPref[u][parentPos + 1 : tree[u].size()] *= parentDfs
    for (int i = parentPos + 1; i <= tree[u].size(); i++)
      multPref[u][i] = multPref[u][i] * parentDfs % m;
    // multSuff[u][0 : parentPos] *= parentDfs
    for (int i = parentPos; i >= 0; i--)
      multSuff[u][i] = multSuff[u][i] * parentDfs % m;
  }

  for (int i = 0; i < tree[u].size(); i++)
  {
    int v = tree[u][i];
    if (v != prv)
      dfs2(v, u, i);
  }
}

int main()
{
  int tt = 0;
  while (scanf("%d %lld", &n, &m) != EOF)
  {
    if (tt++) printf("-----------------------\n");

    for (int i = 0; i < n; i++)
      tree[i].clear(), multPref[i].clear(), multSuff[i].clear();

    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
    }

    for (int i = 0; i < n; i++)
    {
      multPref[i].resize(tree[i].size() + 1, 1);
      multSuff[i].resize(tree[i].size() + 1, 1);
    }

    dfs();
    dfs2();
    for (int i = 0; i < n; i++)
      printf("%lld\n", (res[i] - 1 + m) % m);
  }
  return 0;
}
