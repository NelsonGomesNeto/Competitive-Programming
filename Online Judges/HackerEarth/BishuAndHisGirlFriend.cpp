#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e3;
vector<int> tree[maxN];
int level[maxN];

void dfs(int u)
{
  for (int v: tree[u])
  {
    level[v] = level[u] + 1;
    dfs(v);
  }
}

int main()
{
  int n; scanf("%d", &n); int u, v;
  for (int i = 0; i < n - 1; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    tree[u].push_back(v);
  }
  level[0] = 0; dfs(0);

  int q, ans = 1e9, ansLevel = 1e9; scanf("%d", &q);
  while (q --)
  {
    scanf("%d", &u); u --;
    if (level[u] < ansLevel || (level[u] == ansLevel && u < ans))
      ansLevel = level[u], ans = u;
  }
  printf("%d\n", ans + 1);

  return(0);
}
