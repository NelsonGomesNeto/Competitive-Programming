#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
const lli mod = 1e9 + 7;
vector<int> tree[maxN];

lli memo[maxN][2];
lli dfs(int u = 0, int prv = -1, int prvColor = 0)
{
  lli &ans = memo[u][prvColor];
  if (ans != -1) return ans;

  bool leaf = true;
  ans = 0;

  for (int col = 0; col <= (prvColor ? 0 : 1); col++)
  {
    lli sum = 1;
    for (int v: tree[u])
      if (v != prv)
        sum = (sum * dfs(v, u, col)) % mod, leaf = false;
    ans = (ans + sum) % mod;
  }

  if (leaf)
    ans = prvColor == 1 ? 1 : 2;

  return ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++) tree[i].clear();
    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
    }

    memset(memo, -1, sizeof(memo));
    lli ans = dfs();
    printf("%lld\n", ans);
  }
  return 0;
}