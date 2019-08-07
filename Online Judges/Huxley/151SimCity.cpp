#include <bits/stdc++.h>
using namespace std;
int n;
map<pair<double, double>, int> doubleToInt;

double distance(double p1[], double p2[])
{
  return(sqrt((p1[0] - p2[0])*(p1[0] - p2[0]) + (p1[1] - p2[1])*(p1[1] - p2[1])));
}

double prim(vector<pair<int, double> > graph[])
{
  int visited[n]; memset(visited, 0, sizeof(visited));
  priority_queue<pair<double, int>, vector<pair<double, int> >, greater<pair<double, int> > > pq;
  pq.push({0, 0});
  double totalCost = 0;
  while (!pq.empty())
  {
    double c = pq.top().first; int u = pq.top().second; pq.pop();
    if (visited[u]) continue;
    visited[u] = 1;
    totalCost += c;
    for (auto v: graph[u])
      pq.push({v.second, v.first});
  }
  return(totalCost);
}

int main()
{
  while (scanf("%d", &n) && n)
  {
    doubleToInt.clear();
    vector<pair<int, double> > graph[n];
    double points[n][2];
    for (int i = 0; i < n; i ++)
    {
      double x, y; scanf("%lf %lf", &x, &y);
      // doubleToInt[{x, y}] = i;
      points[i][0] = x; points[i][1] = y;
    }

    for (int i = 0; i < n; i ++)
      for (int j = 0; j < n; j ++)
      {
        if (i == j) continue;
        graph[i].push_back({j, distance(points[i], points[j])});
      }

    double minCost = prim(graph);
    printf("%.2lf\n", minCost);
  }
  return(0);
}