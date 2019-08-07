#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e3; int n, m;
char table[maxN][maxN + 1];
lli f[maxN][maxN], before[maxN][maxN]; int visited[maxN][maxN], id;
int dj[256], di[256];

void fillCycle(int i, int j)
{
  id ++;
  lli size = 0; int bi = i, bj = j;
  while (i >= 0 && j >= 0 && i < n && j < m && !visited[i][j])
  {
    before[i][j] = size ++;
    visited[i][j] = id;
    int ni = di[table[i][j]], nj = dj[table[i][j]];
    i += ni, j += nj;
  }
  if (i >= 0 && j >= 0 && i < n && j < m && visited[i][j] == id)
  {
    size = size - before[i][j];
    while (!f[i][j])
    {
      f[i][j] = size;
      int ni = di[table[i][j]], nj = dj[table[i][j]];
      i += ni, j += nj;
    }
  }
}
lli fillUntilEnd(int i, int j)
{
  if (i < 0 || j < 0 || i >= n || j >= m) return(0);
  if (f[i][j]) return(f[i][j]);
  return(f[i][j] = 1 + fillUntilEnd(i + di[table[i][j]], j + dj[table[i][j]]));
}

int main()
{
  dj['W'] = -1, dj['E'] = 1, dj['N'] = dj['S'] = 0;
  di['W'] = di['E'] = 0, di['N'] = -1, di['S'] = 1;

  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i ++) scanf(" %s", table[i]);

  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      if (!f[i][j])
      {
        fillCycle(i, j);
        fillUntilEnd(i, j);
      }

  // for (int i = 0; i < n; i ++)
  //   for (int j = 0; j < m; j ++)
  //     printf("%lld%c", f[i][j], j < m - 1 ? ' ' : '\n');

  lli sum = 0;
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      sum += f[i][j];
  printf("%lld\n", sum);

  return(0);
}