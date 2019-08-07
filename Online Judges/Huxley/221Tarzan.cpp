#include <bits/stdc++.h>
using namespace std;
int n, d;

double distance(int p1[], int p2[])
{
  return(sqrt((p1[0] - p2[0])*(p1[0] - p2[0]) + (p1[1] - p2[1])*(p1[1] - p2[1])));
}

int bfs(vector<int> graph[])
{
  int visited[n]; memset(visited, 0, sizeof(visited));
  deque<int> q; q.push_back(0);
  while (!q.empty())
  {
    int u = q.front(); q.pop_front();
    if (visited[u]) continue;
    visited[u] = 1;
    for (auto v: graph[u]) q.push_back(v);
  }
  for (int i = 0; i < n; i ++)
    if (!visited[i]) return(0);
  return(1);
}

int main()
{
  scanf("%d %d", &n, &d);
  int tree[n][2]; for (int i = 0; i < n; i ++) scanf("%d %d", &tree[i][0], &tree[i][1]);

  vector<int> graph[n];
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
    {
      if (i == j) continue;
      if (distance(tree[i], tree[j]) <= d)
      {
        graph[i].push_back(j);
        graph[j].push_back(i);
      }
    }

  printf("%s\n", bfs(graph) ? "S" : "N");
  return(0);
}
