#include <bits/stdc++.h>
using namespace std;
const int maxN = 100;
int n, m, source = 0, target, passengers;

vector<pair<int, int>> graph[maxN];
int cost[maxN], previ[maxN], steps[maxN], inf = 1<<20;;
void printPath()
{
  stack<int> s;
  for (int u = target; u != source; u = previ[u]) s.push(u);
  printf("%d", source + 1);
  while (!s.empty())
  {
    printf(" %d", s.top() + 1);
    s.pop();
  }
}
int dijkstra()
{
  for (int i = 0; i < n; i ++) cost[i] = 0, previ[i] = n;
  priority_queue<pair<int, pair<int, int>>> pq; pq.push({0, {0, 0}}); cost[source] = inf, steps[source] = 0;
  while (!pq.empty())
  {
    int u = pq.top().second.first, step = pq.top().second.second; pq.pop();
    for (auto v: graph[u])
    {
      if (v.first == previ[u]) continue;
      int newCost = min(cost[u], v.second);
      if (newCost > cost[v.first] || (newCost == cost[v.first] && u < previ[v.first]) || (newCost == cost[v.first] && u == previ[v.first] && step + 1 < steps[v.first]))
      {
        cost[v.first] = min(cost[u], v.second), previ[v.first] = u, steps[v.first] = step + 1;
        pq.push({-cost[v.first], {v.first, step + 1}});
      }
    }
  }
  return(cost[target]);
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i ++)
  {
    int u, v, c; scanf("%d %d %d", &u, &v, &c); u --, v --;
    graph[u].push_back({v, c});
    graph[v].push_back({u, c});
  }
  scanf("%d %d %d", &source, &target, &passengers); source --, target --;

  int ans = dijkstra() - 1;
  if (ans > 0)
  {
    printPath(); printf("\n");
    printf("%d\n", passengers / ans + (passengers % ans != 0));
  }
  return(0);
}