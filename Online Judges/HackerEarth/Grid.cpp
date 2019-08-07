#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e3;
int n, m, q, si = 0, sj = 0;
char grid[maxN][maxN + 1];

int dist[maxN][maxN], dy[4] = {0, 0, 1, -1}, dx[4] = {1, -1, 0, 0};
int valid(int i, int j)
{
  return(!(i < 0 || i >= n || j < 0 || j >= m));
}
void bfs()
{
  memset(dist, -1, sizeof(dist));
  queue<pair<int, int>> q; q.push({si, sj}); dist[si][sj] = 0;
  while (!q.empty())
  {
    int i = q.front().first, j = q.front().second; q.pop();
    for (int k = 0; k < 4; k ++)
      if (valid(i + dy[k], j + dx[k]) && dist[i + dy[k]][j + dx[k]] == -1 && grid[i + dy[k]][j + dx[k]] == 'O')
        q.push({i + dy[k], j + dx[k]}), dist[i + dy[k]][j + dx[k]] = dist[i][j] + 1;
  }
}

int main()
{
  scanf("%d %d %d", &n, &m, &q);
  for (int i = 0; i < n; i ++) scanf("\n%s", grid[i]);
  scanf("%d %d", &si, &sj); si --, sj --;
  bfs();

  while (q --)
  {
    int di, dj; scanf("%d %d", &di, &dj); di --, dj --;
    printf("%d\n", dist[di][dj]);
  }

  return(0);
}