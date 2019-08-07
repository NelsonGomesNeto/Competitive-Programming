#include <bits/stdc++.h>
using namespace std;
int si, sj, fi, fj;
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
int n, m, d;

int bfs(vector<int> visited[], vector<int> accSum[])
{
  deque<pair<pair<int, int>, int> > queue;
  queue.push_back({{si, sj}, 0});
  while (!queue.empty())
  {
    int i = queue.front().first.first, j = queue.front().first.second, steps = queue.front().second;
    if (i == fi && j == fj) return(steps);
    queue.pop_front();
    if (i < 0 || j < 0 || i >= n || j >= m || visited[i][j] || accSum[i][j] != -1) continue;
    visited[i][j] = 1;
    for (int k = 0; k < 4; k ++)
      queue.push_back({{i + dy[k], j + dx[k]}, steps + 1});
  }
  return(-1);
}

int main()
{
  scanf("%d %d %d", &n, &m, &d);
  vector<char> maze[n]; vector<int> visited[n], accSum[n]; char b;
  for (int i = 0; i < n; i ++)
  {
    getchar();
    for (int j = 0; j < m; j ++)
    {
      scanf("%c", &b);
      maze[i].push_back(b); visited[i].push_back(0); accSum[i].push_back(-1);
      if (b == 'S') si = i, sj = j;
      if (b == 'F') fi = i, fj = j;
      if (b == 'M') accSum[i][j] = d;
    }
  }
  for (int i = 0; i < n; i ++)
  {
    for (int j = 1; j < m; j ++) accSum[i][j] = max(accSum[i][j - 1] - 1, accSum[i][j]);
    for (int j = m - 2; j >= 0; j --) accSum[i][j] = max(accSum[i][j + 1] - 1, accSum[i][j]);
  }
  for (int j = 0; j < m; j ++)
  {
    for (int i = 1; i < n; i ++) accSum[i][j] = max(accSum[i - 1][j] - 1, accSum[i][j]);
    for (int i = n - 2; i >= 0; i --) accSum[i][j] = max(accSum[i + 1][j] - 1, accSum[i][j]);
  }

  int ans = accSum[fi][fj] == -1 ? bfs(visited, accSum) : -1;
  printf("%d\n", ans == -1 ? -1 : ans);

  return(0);
}
