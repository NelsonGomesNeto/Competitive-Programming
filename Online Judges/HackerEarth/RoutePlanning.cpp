#include <bits/stdc++.h>
using namespace std;

/* Explanation:
u and v stations will be connected if the time is divisible by when some bus is present at u
*/

const int maxN = 1e5; int n, m;
set<int> cities[]; // (v, time)
int cost[maxN], inf = 1e7;
// void dijkstra()
// {
//   for (int i = 0; i < n; i ++) cost[i] = inf;
//   priority_queue<pair<int, int>> pq; pq.push({0, 0}); cost[0] = 0;
//   while (!pq.empty())
//   {
//     int u = pq.top().second; pq.pop();
//     for (auto v: graph[u])
//       if (cost[u] + 1 < cost[v.first])
//       {
//         cost[v.first] = cost[u] + 1;
//         pq.push({-cost[v.first], v.first});
//       }
//   }
// }

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= m; i ++)
  {
    int t, u; scanf("%d", &t);
    while (t --)
    {
      scanf("%d", &u); u --;
      graph[i].push_back({u, 0}); graph[u].push_back({i, 0});
    }
  }
  // dijkstra();
  for (int i = 1; i < n; i ++) printf("%d%c", cost[i] == inf ? -1 : cost[i], i < n - 1 ? ' ' : '\n');

  return(0);
}
