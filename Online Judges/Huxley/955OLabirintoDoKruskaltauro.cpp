#include <bits/stdc++.h>
#include <limits.h>
using namespace std;
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
#define inf INT_MAX

int waitTime(int period, int tempo)
{
  return(period - tempo % period);
}

void dijkstra(vector<vector<pair<int, int> > > graph, int **cost, int start, int period)
{
  for (int i = 0; i < period; i ++)
    cost[start][i] = 0;
  priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
  pq.push({cost[start][0], start});
  while (!pq.empty())
  {
    int tempo = pq.top().first, v = pq.top().second; pq.pop();
    for (auto u : graph[v])
    {
      if (u.second == 0 || tempo % u.second == 0)
      {
        if (tempo + 1 < cost[u.first][(tempo + 1) % period])
        {
          cost[u.first][(tempo + 1) % period] = tempo + 1;
          pq.push({tempo + 1, u.first});
        }
      }
      else
      {
        int timeToWait = waitTime(u.second, tempo);
        if (tempo + timeToWait + 1 < cost[u.first][(tempo + timeToWait + 1) % period])
        {
          cost[u.first][(tempo + timeToWait + 1) % period] = tempo + timeToWait + 1;
          pq.push({tempo + timeToWait + 1, u.first});
        }
      }
    }
  }
}

int main()
{
  int run = 0, tests; scanf("%d", &tests);
  while (run < tests)
  {
    int y, x; scanf("%d %d", &y, &x);

    vector<vector<pair<int, int> > > graph(y*x);
    int totalSize = y*x;
    for (int i = 0; i < totalSize; i ++)
    {
      char line[10];
      scanf("%s", line);
      for (int j = 0; line[j] != '\0'; j ++)
      {
        if (line[j] == 'N')
          graph[i].pb(mp(i - x, 0));
        else if (line[j] == 'E')
          graph[i].pb(mp(i + 1, 0));
        else if (line[j] == 'S')
          graph[i].pb(mp(i + x, 0));
        else // 'W'
          graph[i].pb(mp(i - 1, 0));
      }
    }

    int portals, period; scanf("%d %d", &portals, &period);
    for (int i = 0; i < portals; i ++)
    {
      int ui, uj, vi, vj; scanf("%d %d %d %d", &ui, &uj, &vi, &vj);
      graph[ui*x + uj].pb(mp(vi*x + vj, period));
    }

    int **cost = (int**) malloc(totalSize * sizeof(int*));
    for (int i = 0; i < totalSize; i ++)
    {
      cost[i] = (int*) malloc(period * sizeof(int));
      for (int j = 0; j < period; j ++)
        cost[i][j] = inf;
    }

    dijkstra(graph, cost, 0, period);

    int smallestTime = inf;
    for (int i = 0; i < period; i ++)
      smallestTime = min(smallestTime, cost[totalSize - 1][i]);

    printf("%d: %d\n", run, smallestTime);

    free(cost);
    run ++;
  }
  return(0);
}