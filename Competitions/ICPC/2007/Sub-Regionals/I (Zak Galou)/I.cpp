#include <bits/stdc++.h>
#define lli long long int
using namespace std;
vector<int> graph[1000];
int spells[1000][2];
lli inf = 1e18, minMana[1001], hallsMana[1000], cost[1001];

lli dijkstra(int source, int target)
{
  for (int i = 0; i <= 1000; i ++) cost[i] = inf;
  priority_queue<pair<lli, int>, vector<pair<lli, int>>, greater<pair<lli, int>>> pq;
  pq.push({hallsMana[source], source}); cost[source] = hallsMana[source];
  while (!pq.empty())
  {
    int u = pq.top().second; pq.pop();
    for (auto v: graph[u])
      if (cost[u] + hallsMana[v] < cost[v])
        cost[v] = cost[u] + hallsMana[v], pq.push({cost[v], v});
  }
  return(cost[target]);
}

int main()
{
  int m, n, g, k;
  while (scanf("%d %d %d %d", &m, &n, &g, &k) && !(!m && !n && !g && !k))
  {
    for (int i = 0; i < n; i ++) graph[i].clear(), hallsMana[i] = 0;

    for (int i = 0; i < m; i ++) scanf("%d %d", &spells[i][0], &spells[i][1]);

    minMana[0] = 0; for (int i = 1; i <= 1000; i ++) minMana[i] = inf;
    for (int hp = 1; hp <= 1000; hp ++)
      for (int i = 0; i < m; i ++)
        minMana[hp] = min(minMana[hp], minMana[max(0, hp - spells[i][1])] + spells[i][0]);

    // for (int i = 0; i <= 100; i ++)
    //   printf("hp: %d, minMana: %d\n", i, minMana[i]);

    int a, b;
    for (int i = 0; i < g; i ++)
    {
      scanf("%d %d", &a, &b); a --, b --;
      graph[a].push_back(b); graph[b].push_back(a);
    }

    for (int i = 0; i < k; i ++)
    {
      scanf("%d %d", &a, &b); a --;
      hallsMana[a] += minMana[b];
    }

    dijkstra(0, n - 1);
    printf("%d\n", cost[n - 1] == inf ? -1 : cost[n - 1]);
  }
  return(0);
}
