#include <bits/stdc++.h>
#define lli long long int
using namespace std;
 
const int maxN = 1e5; int n, m;
set<int> graph[maxN];
set<int> toVisit;

void dfs(int u)
{
  toVisit.erase(u);

  list<int> now;
  for (int v: toVisit)
    if (!graph[u].count(v))
      now.push_back(v);

  for (int v: now) toVisit.erase(v);
  for (int v: now) dfs(v);
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < n; i ++)
      toVisit.insert(i), graph[i].clear();
    for (int i = 0; i < m; i ++)
    {
      int u, v; scanf("%d %d", &u, &v); u --, v --;
      graph[u].insert(v), graph[v].insert(u);
    }
 
    int ans = 0;
    for (int i = 0; i < n; i ++)
      if (toVisit.count(i))
        ans ++, dfs(i);
    printf("%d\n", ans - 1);
  }
  return 0;
}