#include <bits/stdc++.h>
using namespace std;
int mat[1000][1000], n, m;

int bfs(vector<int> graph[], int start)
{
  int visited[n*m]; memset(visited, 0, sizeof(visited));
  deque<pair<int, int> > queue; queue.push_back({start, 0});
  while (!queue.empty())
  {
    int u = queue.front().first, dist = queue.front().second; queue.pop_front();
    // printf("%d %d (%d, %d)\n", u, mat[u/m][u%m], u / m, u % m);
    if (mat[u/m][u%m] == 0) return(dist);
    if (visited[u]) continue;
    visited[u] = 1;
    for (auto v: graph[u])
      queue.push_back({v, dist + 1});
  }
}

int main()
{
  scanf("%d %d", &n, &m);
  vector<int> graph[n*m];
  int start = 0;
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
    {
      scanf("%d", &mat[i][j]);
      if (mat[i][j] == 3) start = i*m + j;
    }

  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
    {
      if (i && mat[i - 1][j] != 2)
        graph[i*m + j].push_back((i - 1)*m + j);
      if (j && mat[i][j - 1] != 2)
        graph[i*m + j].push_back(i*m + j - 1);
      if ((n - i - 1) && mat[i + 1][j] != 2)
        graph[i*m + j].push_back((i + 1)*m + j);
      if ((m - j - 1) && mat[i][j + 1] != 2)
        graph[i*m + j].push_back(i*m + j + 1);
    }

  int moves = bfs(graph, start);
  printf("%d\n", moves);
  return(0);
}