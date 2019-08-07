#include <bits/stdc++.h>
using namespace std;
int n, m, inf = 1<<20;
int dx[4] = {0, 0, -1, 1}, dy[4] = {1, -1, 0, 0};

int backtrack(vector<vector<int> > graph, int i, int j, int prev)
{
  if (i < 0 || j < 0 || i >= n || j >= m || !graph[i][j]) return(inf);
  if (i == n - 1 && j == m - 1) return(0);
  graph[i][j] = 0;
  int ans = inf;
  for (int k = 0; k < 2; k ++)
    ans = min(ans, (prev >= 2 and prev != -1) + backtrack(graph, i + dy[k], j + dx[k], k));
  for (int k = 2; k < 4; k ++)
    ans = min(ans, (prev < 2 and prev != -1) + backtrack(graph, i + dy[k], j + dx[k], k));
  graph[i][j] = 1;
  return(ans);
}

int main()
{
  scanf("%d %d", &n, &m);
  vector<vector<int> > graph;
  for (int i = 0; i < n; i ++)
  {
    graph.push_back(vector<int>(n));
    int u;
    for (int j = 0; j < m; j ++)
    {
      graph[i].push_back(u);
      scanf("%d", &u);
      graph[i][j] = u;
    }
  }

  int ans = backtrack(graph, 0, 0, -1);
  if (ans >= inf) printf("Welcome to the Upside Down.\n");
  else printf("O caminho tem complexidade: %d\n", ans);
  return(0);
}
