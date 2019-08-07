#include <bits/stdc++.h>
using namespace std;

const int maxN = 502, inf = 1e6; int n, p;
int black[maxN][maxN], white[maxN][maxN];
int blackDist[maxN][maxN], whiteDist[maxN][maxN];

void read(int table[maxN][maxN], int dist[maxN][maxN])
{
  for (int i = 0, ii, jj; i < p; i ++)
  {
    scanf("%d %d", &ii, &jj);
    table[ii][jj] = 1, dist[ii][jj] = 0;
  }
}
void fillDist(int dist[maxN][maxN])
{
  for (int i = 1; i <= n; i ++)
    for (int j = 2; j <= n; j ++)
      dist[i][j] = min(dist[i][j], dist[i][j - 1] + 1);
  for (int j = 1; j <= n; j ++)
    for (int i = 2; i <= n; i ++)
      dist[i][j] = min(dist[i][j], dist[i - 1][j] + 1);
  for (int i = 2; i <= n; i ++)
    for (int j = 2; j <= n; j ++)
      dist[i][j] = min(dist[i][j], dist[i - 1][j - 1] + 1);
}

int count(int dist[maxN][maxN], int otherDist[maxN][maxN])
{
  int ans = 0;
  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= n; j ++)
      ans += max(0, dist[i][j] - otherDist[i][j]);
  return(ans);
}

int main()
{
  scanf("%d %d", &n, &p);
  for (int i = 0; i < maxN; i ++) for (int j = 0; j < maxN; j ++) blackDist[i][j] = whiteDist[i][j] = min(i, j);

  read(black, blackDist); read(white, whiteDist);

  fillDist(blackDist); fillDist(whiteDist);

  int b = count(whiteDist, blackDist), w = count(blackDist, whiteDist);
  printf("%d %d\n", b, w);

  return(0);
}