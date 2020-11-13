#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, m;
vector<int> graph[maxN];
int indegree[maxN];

int memo[maxN];
int dfs(int u)
{
  int &ans = memo[u];
  if (ans != -1) return ans;

  ans = 0;
  for (int v: graph[u])
    ans = max(ans, 1 + dfs(v));
  return ans;
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < n; i++)
      graph[i].clear(), indegree[i] = 0;

    for (int i = 0; i < m; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      graph[u].push_back(v);
      indegree[v]++;
    }

    int ans = 0;
    memset(memo, -1, sizeof(memo));
    for (int i = 0; i < n; i++)
      if (indegree[i] == 0)
        ans = max(ans, dfs(i));
    printf("%d\n", ans);
  }
  return 0;
}