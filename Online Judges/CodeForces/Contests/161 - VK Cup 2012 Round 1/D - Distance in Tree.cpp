#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

const int maxN = 5e4, maxK = 5e2; int n, k;
vector<int> tree[maxN];

int memo[maxN][maxK + 1], ans;
void dfs(int u, int prv)
{
  memo[u][0] = 1;
  for (int v: tree[u])
  {
    if (v == prv) continue;
    dfs(v, u);
    for (int i = 0; i < k; i ++) ans += memo[u][i] * memo[v][k - i - 1];
    for (int i = 0; i < k; i ++) memo[u][i + 1] += memo[v][i];
  }
}

int main()
{
  scanf("%d %d", &n, &k);
  for (int i = 1, u, v; i < n; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    tree[u].push_back(v), tree[v].push_back(u);
  }

  dfs(0, -1);
  DEBUG
  {
    printf("    "); for (int i = 0; i <= k; i ++) printf("%3d%c", i, i < k ? ' ' : '\n');
    for (int  i = 0; i < n; i ++)
    {
      printf("%3d ", i + 1);
      for (int j = 0; j <= k; j ++) printf("%3d%c", memo[i][j], j < k ? ' ' : '\n');
    }
  }
  printf("%d\n", ans);
  return(0);
}