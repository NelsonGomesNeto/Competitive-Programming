#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5;
vector<int> tree[maxN];
int e[maxN], ans[maxN];

void dfs(int u, int prev)
{
  for (int v: tree[u])
  {
    if (v == prev) continue;
    ans[v] = e[v] + ans[u] - 2;
    dfs(v, u);
  }
}

int main()
{
  int n; scanf("%d", &n); int u, v;
  for (int i = 0; i < n - 1; i ++)
  {
    scanf("%d %d", &u, &v); u --, v--;
    tree[u].push_back(v); tree[v].push_back(u);
    e[u] ++, e[v] ++;
  }
  ans[0] = e[0]; dfs(0, -1);

  int q; scanf("%d", &q);
  while (q --)
  {
    scanf("%d", &u); u --;
    printf("%d\n", ans[u]);
  }
  return(0);
}
