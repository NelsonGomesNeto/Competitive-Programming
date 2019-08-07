#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct programa
{
  int edp[21];
};

int niveis, programas, custo, delay, shift;

long double min(long double a, long double b)
{
  return(a < b ? a : b);
}

long double bt(struct programa p[], int i, int j, long double dp[programas + 1][niveis + 1])
{
  if (i == programas)
  {
    return(0);
  }
  if (dp[i][j] == -1)
  {
    dp[i][j] = p[i].edp[j] + bt(p, i + 1, j, dp);
    int k;
    for (k = 0; k < niveis; k ++)
    {
      if (k != j)
      {
        dp[i][j] = min(dp[i][j], bt(p, i + 1, k, dp) + shift + p[i].edp[k]);
      }
    }
    return(dp[i][j]);

  }
  return(dp[i][j]);
}

int main()
{
  while (scanf("%d %d %d %d", &niveis, &programas, &custo, &delay) &&
        !(niveis == 0 && programas == 0 && custo == 0 && delay == 0))
  {
    struct programa app[programas];
    long double dp[programas + 1][niveis + 1];
    int i, j, k, energia, tempo;
    for (i = 0; i <= programas; i ++)
    {
      for (j = 0; j <= niveis; j ++)
      {
        if (i < programas && j < niveis)
        {
          scanf("%d %d", &energia, &tempo);
          app[i].edp[j] = energia * tempo;
        }
        dp[i][j] = -1;
      }
    }
    shift = custo * delay;
    printf("%.0LF\n", bt(app, 0, 0, dp));
  }
  return(0);
}
