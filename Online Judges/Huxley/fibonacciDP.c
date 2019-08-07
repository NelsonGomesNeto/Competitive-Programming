#include <stdio.h>

long double fib(int n, long double dp[])
{
  if (n == 1 || n == 2)
  {
    return(1);
  }
  if (dp[n - 1] == -1)
  {
    dp[n - 1] = fib(n - 1, dp) + fib(n - 2, dp);
  }
  return(dp[n - 1]);
}

int main()
{
  int ith;
  while (scanf("%d", &ith) != EOF)
  {
    long double programacaoDinamica[ith]; int i;
    for (i = 0; i < ith; i ++)
    {
      programacaoDinamica[i] = -1;
    }
    printf("%0.Lf\n", fib(ith, programacaoDinamica));
  }
  return(0);
}
