#include <bits/stdc++.h>
#define lli long long int
using namespace std;
const int maxN = (int) 1e5;

struct City
{
  int name; lli cost;
  bool operator<(const City &b) const { return(cost < b.cost); }
};
vector<City> graph[maxN];
int k, n, m, source, target;
lli cost[maxN], inf = 1e18; int previ[maxN];

int printPath()
{
  int size = 0;
  stack<int> s;
  for (int u = target; u != source; u = previ[u]) s.push(u);
  size = s.size() + 1;
  printf("%d", source + 1);
  while (!s.empty())
  {
    printf("->%d", s.top() + 1);
    s.pop();
  }
  return(size);
}

lli dijkstra()
{
  // bool visited[n]; memset(visited, false, sizeof(visited)); visited[source] = true;
  for (int i = 0; i < n; i ++) cost[i] = inf;
  priority_queue<City> pq; pq.push({source, 0}); cost[source] = 0;
  while (!pq.empty())
  {
    City u = pq.top(); pq.pop();
    for (City &v: graph[u.name])
      if (cost[u.name] + v.cost < cost[v.name])
      {
        cost[v.name] = cost[u.name] + v.cost, previ[v.name] = u.name;
        pq.push({v.name, cost[v.name]});
      }
  }
  return(cost[target]);
}

int main()
{
  scanf("%d %d %d", &k, &n, &m);
  for (int i = 0; i < m; i ++)
  {
    int u, v, t, c; scanf("%d %d %d %d", &u, &v, &t, &c); u --, v --;
    graph[u].push_back({v, c + t * k});
    graph[v].push_back({u, c + t * k});
  }
  scanf("%d %d", &source, &target); source --, target --;
  for (int u = 0; u < n; u ++) for (City &v: graph[u]) if (v.name != target) v.cost += k;

  lli ans = dijkstra();
  if (ans == inf || m > (n * (n - 1) / 2)) printf("Error\n");
  else
  {
    int pathSize = printPath(); printf(" %d %lld\n", pathSize, cost[target]);
  }

  return(0);
}