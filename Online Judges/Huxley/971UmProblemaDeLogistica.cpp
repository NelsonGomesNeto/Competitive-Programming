#include <bits/stdc++.h>
using namespace std;
int inf = INT_MAX;

int prim(vector<pair<int, int> > graph[], int cost[], int visited[], int start)
{
  int total = 0;
  cost[start] = 0;
  priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
  pq.push({cost[start], start});
  while (!pq.empty())
  {
    int c = pq.top().first, v = pq.top().second; pq.pop();
    if (visited[v]) continue;
    visited[v] = 1;
    total += c;
    for (auto u : graph[v])
    {
      cost[u.first] = u.second;
      pq.push({cost[u.first], u.first});
    }
  }
  return(total);
}

int main()
{
  int tests, run = 0; scanf("%d", &tests);
  while (run < tests)
  {
    int numWarehouses; scanf("%d", &numWarehouses);
    //map<pair<int, int>, int> pointToInt;
    //map<int, pair<int, int> > intToPoint;
    int point[numWarehouses][2];
    for (int i = 0; i < numWarehouses; i ++)
    {
      int x, y; scanf("%d %d", &x, &y);
      point[i][0] = x; point[i][1] = y;
      //pointToInt[{x, y}] = i;
      //intToPoint[i] = {x, y};
    }
    vector<pair<int, int> > graph[numWarehouses];
    for (int i = 0; i < numWarehouses; i ++)
      for (int j = 0; j < numWarehouses; j ++)
      {
        //int dist = abs(intToPoint[i].first - intToPoint[j].first) + abs(intToPoint[i].second - intToPoint[j].second);
        int dist = abs(point[i][0] - point[j][0]) + abs(point[i][1] - point[j][1]);
        graph[i].push_back({j, dist});
      }

    int cost[numWarehouses], visited[numWarehouses];
    for (int i = 0; i < numWarehouses; i ++)
    {
      cost[i] = inf; visited[i] = 0;
    }
    int minCost = prim(graph, cost, visited, 0);

    printf("%d: %d\n", run, minCost);
    run ++;
  }
  return(0);
}