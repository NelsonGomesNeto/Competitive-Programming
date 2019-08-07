#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 100, inf = 1e9; int n, x;
int mat[maxN][maxN], wall[maxN][maxN][4], dist[maxN][maxN];
lli force[2*(maxN*maxN - maxN) - 1];
int dj[4] = {1, -1, 0, 0}, di[4] = {0, 0, 1, -1};

int dijkstra()
{
  for (int i = 0; i < n; i ++) for (int j = 0; j < n; j ++) dist[i][j] = inf;
  priority_queue<pair<int, int>> pq; pq.push({0, x}); dist[x / n][x % n] = 0;
  while (!pq.empty())
  {
    int u = pq.top().second, d = -pq.top().first; pq.pop();
    int i = u / n, j = u % n;
    if (d > dist[i][j]) continue;
    if (i == 0 || j == 0 || i == n - 1 || j == n - 1) return(d);

    for (int k = 0; k < 4; k ++)
    {
      int ni = i + di[k], nj = j + dj[k];
      if (dist[i][j] + force[wall[i][j][k]] < dist[ni][nj])
        pq.push({-(dist[ni][nj] = dist[i][j] + force[wall[i][j][k]]), ni*n + nj});
    }
  }
  return(inf);
}

int main()
{
  int t = 0;
  while (scanf("%d %d", &n, &x) != EOF)
  {
    for (int i = 0, end = 2*(n*n - n) - 1; i <= end; i ++)
      scanf("%lld", &force[i]);

    for (int i = 0, a = 0; i < n; i ++)
      for (int j = 0; j < n; j ++)
        mat[i][j] = a ++;

    for (int i = 0, w = 0; i < n - 1; i ++)
    {
      for (int j = 0; j < n - 1; j ++, w ++)
        wall[i][j][0] = wall[i][j + 1][1] = w;
      for (int j = 0; j < n; j ++, w ++)
        wall[i][j][2] = wall[i + 1][j][3] = w;
    }

    int ans = dijkstra();
    printf("caso %d: %d\n", ++ t, ans);
  }

  return(0);
}
/*
 0 < 0>  1 < 1>  2 < 2>  3
 ^       ^       ^       ^
 3       4       5       6
 v       v       v       v
 4 < 7>  5 < 8>  6 < 9>  7
 ^       ^       ^       ^
10      11      12      13
 v       v       v       v
 8 <14>  9 <15> 10 <16> 11
 ^       ^       ^       ^
17      18      19      20
 v       v       v       v
12 <21> 13 <22> 14 <23> 15
*/