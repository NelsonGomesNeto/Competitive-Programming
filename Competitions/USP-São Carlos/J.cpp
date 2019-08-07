#include <bits/stdc++.h>
using namespace std;
int n, k;

int bfs(vector<int> graph[], int visited[], int source)
{
  int perLevel[n + 1]; memset(perLevel, 0, sizeof(perLevel));
  deque<pair<int, int> > q; q.push_back({source, 0});
  int finalLevel = 0;
  while (!q.empty())
  {
    int u = q.front().first, l = q.front().second; q.pop_front();
    finalLevel = max(finalLevel, l);
    perLevel[l] ++;
    visited[u] = 1;
    for (auto v: graph[u])
      q.push_back({v, l + 1});
  }
  int sum[finalLevel + 1]; sum[0] = 0;
  for (int i = 0; i < finalLevel; i ++) sum[i + 1] = sum[i] + perLevel[i];

  int ans = finalLevel <= k ? sum[finalLevel] : 0;
  for (int i = k + 1; i <= finalLevel; i ++)
    ans = max(ans, sum[i] - sum[i - (k + 1)]);
  return(ans);
}

int main()
{
  scanf("%d %d", &n, &k);
  vector<int> graph[n];
  for (int i = 0; i < n - 1; i ++)
  {
    int u, v; scanf("%d %d", &u, &v); u --; v --;
    graph[u].push_back(v);
  }

  int ans = 0, visited[n]; memset(visited, 0, sizeof(visited));
  for (int i = 0; i < n; i ++)
  {
    if (!visited[i])
      ans = max(ans, bfs(graph, visited, i));
  }
  printf("%d\n", ans);
  return(0);
}