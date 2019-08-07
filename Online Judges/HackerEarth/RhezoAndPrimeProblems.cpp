#include <bits/stdc++.h>
#define lli long long int
using namespace std;

long long int inf = INT_MAX;

lli max(lli a, lli b)
{
  return(a > b ? a : b);
}

lli solve(lli **dp, int sieve[], int problem[], int done, int i, int end)
{
  if (i == end)
  {
    if (!sieve[done] and done != 0)
      return((lli) -inf);
    return((lli) 0 );
  }
  if (dp[done][i] == -1)
  {
    dp[done][i] = -inf;
    dp[done][i] = max(dp[done][i], solve(dp, sieve, problem, done + 1, i + 1, end) + problem[i]);
    if (sieve[done] || done == 0)
      dp[done][i] = max(dp[done][i], solve(dp, sieve, problem, 0, i + 1, end));
  }
  return(dp[done][i]);
}

int main()
{
  int problems; scanf("%d", &problems);
  int problem[problems];
  for (int i = 0; i < problems; i ++)
    scanf("%d", &problem[i]);

  int sieve[problems + 1];
  for (int i = 0; i <= problems; i ++)
    sieve[i] = 1;

  sieve[0] = sieve[1] = 0;
  sieve[2] = 1;
  for (int i = 2; i <= problems; i ++)
    if (sieve[i])
      for (int j = 2; i*j <= problems; j ++)
        sieve[i*j] = 0;

  lli **dp = (lli**) malloc((problems + 1) * sizeof(lli*));
  for (int i = 0; i <= problems; i ++)
  {
    dp[i] = (lli*) malloc((problems + 1) * sizeof(lli));
    for (int j = 0; j <= problems; j ++)
      dp[i][j] = -1;
  }

  lli answer = solve(dp, sieve, problem, 0, 0, problems);
  printf("%Ld\n", answer);

  free(dp);

  return(0);
}