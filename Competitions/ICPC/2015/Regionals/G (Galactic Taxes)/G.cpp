#include <bits/stdc++.h>
#define lli long long int
using namespace std;
int n, m; double inf = 1e40;

double dijkstra(vector<vector<int> > graph[], int source, double t)
{
  double cost[n]; for (int i = 0; i < n; i ++) cost[i] = inf;
  cost[0] = 0;
  priority_queue<pair<double, int>, vector<pair<double, int> >, greater<pair<double, int> > > pq;
  pq.push({0, 0});
  while (!pq.empty())
  {
    double price = pq.top().first; int u = pq.top().second; pq.pop();
    for (auto v: graph[u])
    {
      double nextCost = cost[u] + v[1]*t + v[2];
      if (nextCost < cost[v[0]])
      {
        cost[v[0]] = nextCost;
        pq.push({nextCost, v[0]});
      }
    }
  }
  return(cost[n - 1]);
}

double ternarySearch(vector<vector<int> > graph[], double lo, double hi)
{
  if (lo >= hi - 1e-12)
    return(dijkstra(graph, 0, lo));

  double midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi) / 3;
  double elo = dijkstra(graph, 0, midlo), ehi = dijkstra(graph, 0, midhi);
  if (elo > ehi) return(ternarySearch(graph, lo, midhi));
  return(ternarySearch(graph, midlo, hi));
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    vector<vector<int> > graph[n];
    for (int i = 0; i < m; i ++)
    {
      int u, v, a, b; scanf("%d %d %d %d", &u, &v, &a, &b); u --; v --;
      graph[u].push_back({v, a, b});
      graph[v].push_back({u, a, b});
    }

    double ans = ternarySearch(graph, 0, 24*60);
    printf("%.5lf\n", ans);
  }
  return(0);
}
