#include <bits/stdc++.h>
using namespace std;
#define DEBUG if(0)

int main()
{
  int n, m; scanf("%d %d", &n, &m);
  pair<int, int> cost[n]; int c;
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &c);
    cost[i] = {c, i};
  }
  sort(cost, cost+n);
  int nCost[n]; for (int i = 0; i < n; i ++) nCost[cost[i].second] = cost[i].first;

  DEBUG for (int i = 0; i < n; i ++) printf("%d %d\n", cost[i].first, cost[i].second);
  DEBUG printf("\n");
  DEBUG for (int i = 0; i < n; i ++) printf("%d %d\n", nCost[i], i);
  DEBUG printf("\n");

  vector<int> graph[n]; int u, v;
  for (int i = 0; i < m; i ++)
  {
    scanf("%d %d", &u, &v); u --; v --;
    graph[v].push_back(u);
    graph[u].push_back(v);
  }

  int ans = 0, removed[n]; memset(removed, 0, sizeof(removed));
  for (int i = n - 1; i >= 0; i --)
  {
    int now = cost[i].second, k = 0; removed[now] = 1;
    for (auto j: graph[now])
      if (!removed[j]) ans += nCost[j];
  }
  printf("%d\n", ans);

  return(0);
}