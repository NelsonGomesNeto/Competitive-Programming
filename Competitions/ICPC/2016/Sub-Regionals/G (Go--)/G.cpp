#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

const int maxN = 500, maxP = 500; int n, p;
int table[maxN + 1][maxN + 1];
int sum[3][maxN + 1][maxN + 1];

int query(int t, int loi, int loj, int hii, int hij)
{
  return(sum[t][hii][hij] - sum[t][loi - 1][hij] - sum[t][hii][loj - 1] + sum[t][loi - 1][loj - 1]);
}

int count(int x)
{
  int ans = 0;
  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= n; j ++)
      for (int k = 0; k <= min(n - i, n - j); k ++)
        ans += (query(x, i, j, i + k, j + k) > 0) && (query(x == 1 ? 2 : 1, i, j, i + k, j + k) == 0);
  return(ans);
}

void read(int t)
{
  for (int i = 0, ii, jj; i < p; i ++)
  {
    scanf("%d %d", &ii, &jj);
    table[ii][jj] = t;
  }
}

int main()
{
  scanf("%d %d", &n, &p);
  read(1);
  read(2);

  DEBUG {
    for (int i = 1; i <= n; i ++)
    {
      for (int j = 1; j <= n; j ++)
        printf("%d", table[i][j]);
      printf("\n");
    }
  }

  for (int t = 1; t <= 2; t ++)
  {
    for (int i = 1; i <= n; i ++)
    {
      sum[t][i][1] = table[i][1] == t;
      for (int j = 2; j <= n; j ++)
        sum[t][i][j] = sum[t][i][j - 1] + (table[i][j] == t);
    }
    for (int j = 1; j <= n; j ++)
      for (int i = 2; i <= n; i ++)
        sum[t][i][j] += sum[t][i - 1][j];
    DEBUG {
      for (int i = 0; i <= n; i ++)
      {
        for (int j = 0; j <= n; j ++)
          printf("%2d", sum[t][i][j]);
        printf("\n");
      }
      printf("---------------\n");
    }
  }

  int b = 0, w = 0;
  b = count(1), w = count(2);
  printf("%d %d\n", b, w);

  return(0);
}