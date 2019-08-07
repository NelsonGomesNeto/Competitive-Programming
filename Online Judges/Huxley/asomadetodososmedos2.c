#include <stdio.h>
#define MAX 9999999999999
int eventos; long long int medoMax;

struct evento
{
  long long int tristeza, medo;
};

long long int min(long long int a, long long int b)
{
  return(a < b ? a : b);
}

long long int bt(struct evento e[], long long int dp[][medoMax + 10], int p[][medoMax + 10], int i, long long int medo)
{
  int j;
  for (i = 1; i <= eventos; i ++)
  {
    for (j = 0; j <= medo; j ++)
    {
      if (e[i - 1].medo <= j)
      {
        dp[i][j] = min(dp[i - 1][j], e[i - 1].tristeza + dp[i - 1][j - e[i - 1].medo]);
        if (e[i - 1].tristeza + dp[i - 1][j - e[i - 1].medo] < dp[i][j])
        {
          p[i][j] = 1;
        }
        else
        {
          p[i][j] = 0;
        }
      }
      else
      {
        p[i][j] = 0;
        dp[i][j] = dp[i - 1][j];
      }
    }
  }
  return(dp[i][medo]);
}

int main()
{
  scanf("%d %lld", &eventos, &medoMax);
  struct evento eve[eventos]; int i, j;
  long long int DP[eventos][medoMax + 10];
  int path[eventos][medoMax + 10];
  for (i = 0; i < eventos; i ++)
  {
    scanf("%lld %lld", &eve[i].tristeza, &eve[i].medo);
    for (j = 0; j < medoMax + 10; j ++)
    {
      DP[i][j] = -1;
      path[i][j] = -1;
    }
  } DP[i][0] = -1; path[i][0] = -1;

  bt(eve, DP, path, eventos, medoMax);
  printf("%lld\n", DP[0][0]);
  for (i = 0; i < eventos; i ++)
  {
    printf("%d ~ ", i);
    for (j = 0; j <= medoMax; j ++)
    {
      printf("%d ", path[i][j]);
    } printf("\n");
  }
  return(0);
}
