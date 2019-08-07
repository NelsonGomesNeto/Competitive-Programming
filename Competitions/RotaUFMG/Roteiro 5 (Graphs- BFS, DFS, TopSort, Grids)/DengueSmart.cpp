#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
int n;

int bfs(vector<int> graph[], int source, int level[])
{
  deque<pair<int, int> > queue;
  queue.push_back({source, 0});
  while (!queue.empty())
  {
    int u = queue.front().first, l = queue.front().second; queue.pop_front();
    if (level[u] != -1) continue;
    level[u] = l;
    for (auto v: graph[u])
      queue.push_back({v, l + 1});
  }

  int v1 = 0;
  for (int i = 0; i < n; i ++)
    if (level[i] > level[v1])
      v1 = i;
  return(v1);
}

int main()
{
  int t = 0;
  while (scanf("%d", &n) && n)
  {
    if (t ++) printf("\n");

    vector<int> graph[n]; int u, v;
    for (int i = 0; i < n - 1; i ++)
    {
      scanf("%d %d", &u, &v); u --; v --;
      graph[u].push_back(v);
      graph[v].push_back(u);
    }

    int level[n]; memset(level, -1, sizeof(level));
    int v1 = bfs(graph, 0, level);
    DEBUG printf("%d\n", v1);

    memset(level, -1, sizeof(level));
    bfs(graph, v1, level);

    pair<int, int> wtf[n];
    for (int i = 0; i < n; i ++)
      wtf[i] = {level[i], i};
    sort(wtf, wtf+n);
    DEBUG for (int i = 0; i < n; i ++)
      printf("(%d, %d)%c", wtf[i].first, wtf[i].second, i < n - 1 ? ' ' : '\n');

    int diameter = 0;
    for (int i = 0; i < n; i ++)
      if (level[i] > diameter && graph[i].size() <= 1)
        diameter = level[i];

    int target = diameter / 2, midNode = 0;
    for (int i = 0; i < n; i ++)
      if (abs(level[i] - target) < abs(level[midNode] - target) && graph[i].size() > 1)
        midNode = i;
      else if (abs(level[i] - (target + 1)) < abs(level[midNode - (target + 1)]) && graph[i].size() > 1)
        midNode = i;

    printf("Teste %d\n%d\n", t, midNode + 1);
  }

  return(0);
}
