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
  if (dp[i][medo] != -1)
  {
    return(dp[i][medo]);
  }

  if (i == eventos - 1)
  {
    if (e[i].medo <= medoMax)
    {
      p[i][medo] = 1;
      dp[i][medo] = e[i].tristeza;
    }
    else
    {
      p[i][medo] = 0;
      dp[i][medo] = 0;
    }
    return(dp[i][medo]);
  }

  long long int pega = e[i].tristeza + bt(e, dp, p, i + 1, medo);
  long long int naoPega = MAX;
  if (medo + e[i].medo <= medoMax)
  {
    naoPega = bt(e, dp, p, i + 1, medo + e[i].medo);
  }
  dp[i][medo] = min(pega, naoPega);
  if (pega < naoPega)
  {
    p[i][medo] = 1;
  }
  else
  {
    p[i][medo] = 0;
  }

  return(dp[i][medo]);
}

int main()
{
  scanf("%d %lld", &eventos, &medoMax);
  struct evento eve[eventos]; int i, j;
  long long int DP[eventos + 10][medoMax + 10];
  int path[eventos + 10][medoMax + 10];
  for (i = 0; i < eventos; i ++)
  {
    scanf("%lld %lld", &eve[i].tristeza, &eve[i].medo);
    for (j = 0; j < medoMax + 10; j ++)
    {
      DP[i][j] = -1;
      path[i][j] = -1;
    }
  }
  for (j = 0; j < medoMax + 10; j ++)
  {
    DP[i][j] = -1; path[i][j] = -1;
  }

  bt(eve, DP, path, 0, 0);
  printf("%lld\n", DP[0][0]);

  for (i = 0; i < eventos; i ++)
  {
    printf("%d ~ ", i);
    for (j = 0; j <= medoMax; j ++)
    {
      if (DP[i][j] != -1)
        printf("%lld ", DP[i][j]);
    } printf("\n");
  } printf("\n");

  for (i = 0; i < eventos; i ++)
  {
    printf("%d ~ ", i);
    for (j = 0; j < 2; j ++)
    {
      printf("%d ", path[i][j]);
    } printf("\n");
  }
  return(0);
}
