#include <bits/stdc++.h>
using namespace std;

void dfs(vector<int> graph[], int u, int visited[])
{
  if (visited[u]) return;
  visited[u] = 1;
  for (auto v: graph[u]) dfs(graph, v, visited);
}

int main()
{
  int n, m; scanf("%d %d", &n, &m);
  vector<int> graph[n];
  set<int> knowns[n];
  for (int i = 0; i < n; i ++)
  {
    int mm, v; scanf("%d", &mm);
    while (mm --)
    {
      scanf("%d", &v);
      knowns[i].insert(v);
    }
  }
  for (int i = 0; i < n; i ++)
    for (int j = i + 1; j < n; j ++)
      for (auto l: knowns[i])
        if (knowns[j].count(l))
        {
          graph[i].push_back(j); graph[j].push_back(i);
          break;
        }

  int visited[n]; memset(visited, 0, sizeof(visited));
  int groups = 0, hasSome = 0;
  for (int i = 0; i < n; i ++)
  {
    if (!visited[i])
    {
      groups ++;
      dfs(graph, i, visited);
    }
    if (knowns[i].size()) hasSome = 1;
  }
  printf("%d\n", groups - 1 + !hasSome);

  return(0);
}