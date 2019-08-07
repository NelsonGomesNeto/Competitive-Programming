#include <bits/stdc++.h>
using namespace std;

vector<int> tree[(int) 1e5];
double dfs(int u, int prev)
{
  double ans = 0;
  for (int v: tree[u])
    if (v != prev)
      ans += (double) (1 + dfs(v, u)) / (tree[u].size() - (u != 0));
  return(ans);
}

int main()
{
  int n; scanf("%d", &n);
  for (int i = 0; i < n - 1; i ++)
  {
    int u, v; scanf("%d %d", &u, &v); u --, v --;
    tree[u].push_back(v); tree[v].push_back(u);
  }

  double ans = dfs(0, -1);
  printf("%lf\n", ans);
  return(0);
}