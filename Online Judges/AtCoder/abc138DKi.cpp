#include <bits/stdc++.h>
#define lli long long int
using namespace std;
 
const int maxN = 2e5; int n, q;
vector<int> tree[maxN];
int cnt[maxN];
 
void dfs(int u = 0, int prv = -1)
{
  if (prv != -1) cnt[u] += cnt[prv];
  for (int v: tree[u])
    if (v != prv)
      dfs(v, u);
}
 
int main()
{
  scanf("%d %d", &n, &q);
  for (int i = 0, u, v; i < n - 1; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    tree[u].push_back(v), tree[v].push_back(u);
  }
 
  while (q --)
  {
    int p, x; scanf("%d %d", &p, &x); p --;
    cnt[p] += x;
  }
  dfs();
 
  for (int i = 0; i < n; i ++)
    printf("%d%c", cnt[i], i < n - 1 ? ' ' : '\n');
 
  return(0);
}