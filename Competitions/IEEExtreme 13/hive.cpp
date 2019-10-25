#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100+2; int n, m;
int mat[maxN][maxN];
int value[maxN][maxN];

int dieven[6] = {-1, 1, 0, -1, 1, 0}, djeven[6] = {-1, -1, -1, 0, 0, 1};
int diodd[6] = {-1, 1, 0, -1, 1, 0}, djodd[6] = {0, 0, -1, 1, 1, 1};

bool valid(int i, int j) { return !(i < 0 || j < 0 || i > n || j > m); }
int floodFill(int i, int j)
{
  if (i < 0 || j < 0 || i > n || j > m || mat[i][j] != 1) return 0;
  mat[i][j] = 2;
  int ans = 0, ni, nj;
  for (int k = 0; k < 6; k ++)
  {
    if (i & 1)
      ni = i + dieven[k], nj = j + djeven[k];
    else
      ni = i + diodd[k], nj = j + djodd[k];
    if (valid(ni, nj) && mat[ni][nj] == 0)
      ans ++;
    ans += floodFill(ni, nj);
  }
  mat[i][j] = 1;
  return ans;
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= m - !(i & 1); j ++)
      scanf("%d", &mat[i][j]);

  // for (int i = 1; i <= n; i ++)
  //   for (int j = 1; j <= m - !(i & 1); j ++)
  //     printf("%d%c", mat[i][j], j <= m - !(i & 1) - 1 ? ' ' : '\n');

  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= m - !(i & 1); j ++)
      value[i][j] = floodFill(i, j);
  // for (int i = 0; i <= n + 1; i ++)
  //   for (int j = 0; j <= m - !(i & 1) + 1; j ++)
  //     printf("%d%c", mat[i][j], j <= m - !(i & 1) ? ' ' : '\n');
  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= m - !(i & 1); j ++)
      if (mat[i][j] < 0)
        mat[i][j] = 0;

  DEBUG for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= m - !(i & 1); j ++)
      printf("%d%c", value[i][j], j <= m - !(i & 1) - 1 ? ' ' : '\n');

  int q; scanf("%d", &q);
  while (q --)
  {
    char op; int qi, qj;
    scanf(" %c %d %d", &op, &qi, &qj);
    DEBUG printf("-- %c %d %d\n", op, qi, qj);
    if (op == 'a')
    {
      if (mat[qi][qj] == 0)
      {
        mat[qi][qj] = 1;
        for (int i = 1; i <= n; i ++)
          for (int j = 1; j <= m - !(i & 1); j ++)
            value[i][j] = floodFill(i, j);
        DEBUG for (int i = 0; i <= n + 1; i ++)
          for (int j = 0; j <= m - !(i & 1) + 1; j ++)
            printf("%d%c", mat[i][j], j <= m - !(i & 1) ? ' ' : '\n');
        DEBUG for (int i = 1; i <= n; i ++)
          for (int j = 1; j <= m - !(i & 1); j ++)
            printf("%d%c", value[i][j], j <= m - !(i & 1) - 1 ? ' ' : '\n');
        for (int i = 1; i <= n; i ++)
          for (int j = 1; j <= m - !(i & 1); j ++)
            if (mat[i][j] < 0)
              mat[i][j] = 0;
      }
    }
    else printf("%d\n", value[qi][qj]);
  }

  return 0;
}