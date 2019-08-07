#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1000; int n, m;
int mat[maxN][maxN], path[maxN*maxN], pathSize;

int di[4] = {1, 0, -1, 0}, dj[4] = {0, 1, 0, -1};
char dir[4][10] = {"Sul", "Leste", "Norte", "Oeste"};
bool solve(int i = 0, int j = 0, int d = 0)
{
  if (i < 0 || j < 0 || i >= n || j >= m || !mat[i][j]) return(false);
  if (i == n - 1 && j == m - 1) { pathSize = d; return(true); }
  mat[i][j] = 0;
  for (int k = 0; k < 4; k ++)
    if (solve(i + di[k], j + dj[k], d + 1))
    {
      path[d] = k;
      return(true);
    }
  mat[i][j] = 1;
  return(false);
}
void printPath()
{
  bool first = true;
  for (int i = 0; i < pathSize; i ++)
  {
    int j = i;
    while (j < pathSize && path[i] == path[j]) j ++;
    if (!first) printf(", ");
    printf("%d*%s", j - i, dir[path[i]]);
    first = false;
    i = j - 1;
  }
  printf("\n");
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      scanf("%d", &mat[i][j]);

  if (!solve())
    printf("Welcome to the Upside Down.\n");
  else
    printPath();

  return(0);
}