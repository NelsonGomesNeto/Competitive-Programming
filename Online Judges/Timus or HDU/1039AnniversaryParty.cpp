#include <bits/stdc++.h>
using namespace std;

const int maxN = 6e3; int n;
int value[maxN];
int indegree[maxN];
vector<int> supervisors[maxN];

int memo[maxN][2];
int dfs(int u, bool took = false)
{
  if (memo[u][took] == -1)
  {
    int take = value[u] * (!took), nottake = 0;
    for (int v: supervisors[u])
    {
      nottake += dfs(v, false);
      take += dfs(v, true);
    }
    memo[u][took] = max(take, nottake);
  }
  return(memo[u][took]);
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) scanf("%d", &value[i]);
  for (int u, v; scanf("%d %d", &u, &v) != EOF;)
  {
    u --, v --;
    supervisors[v].push_back(u);
    indegree[u] ++;
  }

  memset(memo, -1, sizeof(memo));
  int ans = 0;
  for (int i = 0; i < n; i ++)
    if (indegree[i] == 0)
      ans = dfs(i);
  printf("%d\n", ans);

  return(0);
}