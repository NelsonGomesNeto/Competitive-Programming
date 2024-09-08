#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, k;
vector<int> tree[maxN];
int a[maxN];
int subtreeXor[maxN];

int level[maxN];
void dfs(int u = 0, int prv = -1)
{
  subtreeXor[u] = a[u];
  for (int v: tree[u])
    if (v != prv)
    {
      level[v] = level[u] + 1;
      dfs(v, u);
      subtreeXor[u] ^= subtreeXor[v];
    }
}

void dfs2(int u = 0, int prv = -1)
{
  for (int v: tree[u])
    if (v != prv)
      dfs2(v, u);
}

pair<int, int> order[maxN];
map<int, int> memo[maxN][10];
int solve(int i = 1, int kk = min(9, k - 1), int curr = subtreeXor[0])
{
  if (kk == 0) return 0;
  if (i == n) return 0;

  if (memo[i][kk].count(curr)) return memo[i][kk][curr];
  int &ans = memo[i][kk][curr];

  DEBUG printf("\t%d %d - %d - %d %d\n", i, kk, curr, subtreeXor[i], curr ^ subtreeXor[i]);
  if ((curr ^ subtreeXor[i]) == subtreeXor[i])
    return ans = 1;
  ans = 0;
  if (solve(i + 1, kk, curr))
    return ans = 1;
  if (solve(i + 1, kk - 1, curr ^ subtreeXor[i]))
    return ans = 1;
  return ans;
}
map<lli, int> cnt;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    for (int i = 0; i < n; i++)
    {
      tree[i].clear();
      for (int j = 0; j < 10; j++) memo[i][j].clear();
    }

    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
    }
    cnt.clear();

    dfs();
    for (int i = 0; i < n; i++) cnt[subtreeXor[i]]++;
    // for (int i = 0; i < n; i++) order[i] = make_pair(level[i], i);
    // sort(order, order+n);
    // reverse(order, order+n);

    // bool can = solve();
    // bool can = k == n;
    // for (int i = 1; i < n; i++) if (a[i - 1] != a[i]) can = false;

    bool can = false;
    for (int i = 1; i < n; i++)
      if ((subtreeXor[0] ^ subtreeXor[i]) == subtreeXor[i])
        can = true;
    if (k > 2)
      for (int i = 1; i < n; i++)
        if (subtreeXor[0] == subtreeXor[i] || cnt[subtreeXor[0] ^ subtreeXor[i]] > 1)
          can = true;
    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}
