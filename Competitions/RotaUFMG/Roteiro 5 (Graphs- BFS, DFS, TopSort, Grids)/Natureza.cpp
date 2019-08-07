#include <bits/stdc++.h>
using namespace std;
int c, r;

pair<int, int> bfs(vector<int> graph[], int source)
{
  int level[c]; memset(level, -1, sizeof(level));
  deque<pair<int, int> > queue; queue.push_back({source, 0});
  while (!queue.empty())
  {
    int u = queue.front().first, at = queue.front().second; queue.pop_front();
    if (level[u] != -1) continue;
    level[u] = at;
    for (auto v: graph[u])
      queue.push_back({u, at + 1});
  }
  pair<int, int> furthest = {0, -1};
  for (int i = 0; i < c; i ++)
    if (level[i] > furthest.second)
      furthest = {i, level[i]};
  return(furthest);
}

int main()
{
  while (scanf("%d %d", &c, &r) && !(!c && !r))
  {
    map<const char*, int> stringToInt;
    char a[50], b[50];
    for (int i = 0; i < c; i ++)
    {
      scanf("\n%s", a);
      stringToInt[a] = i;
    }
    vector<int> graph[c];
    for (int i = 0; i < r; i ++)
    {
      scanf("\n%s %s", a, b);
      graph[stringToInt[a]].push_back(stringToInt[b]);
    }

    pair<int, int> mid = bfs(graph, 0);
    printf("%d %d\n", mid.first, mid.second);
    pair<int, int> ans = bfs(graph, mid.first);
    printf("%d\n", ans.second);
  }
  return(0);
}