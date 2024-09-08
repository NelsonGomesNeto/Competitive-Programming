#include <bits/stdc++.h>
using namespace std;

const int maxN = 100, inf = 1e7; int n, q;
vector<pair<int, int>> tree[maxN];

vector<int> dfs(int u = 0, int prv = -1)
{
  vector<int> ans; for (int i = 0; i <= n; i ++) ans.push_back(inf); ans[0] = 0;
  if (tree[u].size() == 1) return(ans);

  int branches = 0;
  for (auto i: tree[u]) if (i.first != prv) branches ++;

  if (branches == 1)
  {
    vector<int> a; int r = -1;
    for (auto i: tree[u])
      if (i.first != prv)
        a = dfs(i.first, u), r = i.second;
    for (int i = 0; i < n; i ++)
      if (a[i + 1] == inf)
      {
        a[i + 1] = r + (i == 0 ? 0 : a[i]);
        return(a);
      }
  }
  if (branches == 2)
  {
    vector<int> a, b; int ra = -1, rb, sa, ssa, sb, ssb;
    for (auto i: tree[u])
      if (i.first != prv)
      {
        if (ra == -1) a = dfs(i.first, u), ra = i.second;
        else b = dfs(i.first, u), rb = i.second;
      }
    for (int i = 0; i < n; i ++)
      if (a[i + 1] == inf)
      {
        a[i + 1] = ra + (i == 0 ? 0 : a[i]);
        sa = i + 1, ssa = a[i + 1];
        break;
      }
    for (int i = 0; i < n; i ++)
      if (b[i + 1] == inf)
      {
        b[i + 1] = rb + (i == 0 ? 0 : b[i]);
        sb = i + 1, ssb = b[i + 1];
        break;
      }
    // printf("-- %d | %d %d | %d %d | %d %d\n", u + 1, ra, rb, sa, sb, ssa, ssb);
    for (int i = 0; i <= n; i ++)
      for (int j = 0; j <= n; j ++)
        if (i + j <= n)
          ans[i + j] = min(ans[i + j], a[i] + b[j]);
    // for (int i = 0; i <= n; i ++) printf("\t-- %d %d\n", i, ans[i]);
    return(ans);
  }
}

int main()
{
  scanf("%d %d", &n, &q);
  int sum = 0;
  for (int i = 0, u, v, a; i < n - 1; i ++)
  {
    scanf("%d %d %d", &u, &v, &a); u --, v --;
    sum += a;
    tree[u].push_back({v, a}), tree[v].push_back({u, a});
  }

  vector<int> ans = dfs();
  // for (int i = 0; i <= n; i ++) printf("%d %d\n", i, ans[i]);
  printf("%d\n", sum - ans[n - q - 1]);

  return(0);
}