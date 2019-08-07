#include <bits/stdc++.h>
long long inf = 1e10;

long long max(long long a, long long b)
{
  return(a > b ? a : b);
}

long long qCards;

long long solve(long long **dp, long long cards[], long long lo, long long hi)
{
  if (lo >= hi)
    return(0);

  if (dp[lo][hi] == -inf)
  {
    long long aux = -inf;
    long long me = cards[lo], greedy;
    long long theMid = solve(dp, cards, lo + 1, hi - 1);
    if (cards[lo + 1] >= cards[hi])
    {
      greedy = cards[lo + 1];
      aux = max(aux, solve(dp, cards, lo + 2, hi) + (me - greedy));
    }
    else
    {
      greedy = cards[hi];
      aux = max(aux, theMid + (me - greedy));
    }
    me = cards[hi];
    if (cards[lo] >= cards[hi - 1])
    {
      greedy = cards[lo];
      aux = max(aux, theMid + (me - greedy));
    }
    else
    {
      greedy = cards[hi - 1];
      aux = max(aux, solve(dp, cards, lo, hi - 2) + (me - greedy));
    }
    dp[lo][hi] = aux;
  }

  return(dp[lo][hi]);
}

int main()
{
  long long run = 0, qCards;
  while (scanf("%Ld", &qCards) && qCards != 0)
  {
    run ++;
    long long cards[qCards];
    for (long long i = 0; i < qCards; i ++)
      scanf("%Ld", &cards[i]);

    long long **dp = (long long**) malloc(qCards * sizeof(long long*));
    for (long long i = 0; i < qCards; i ++)
    {
      dp[i] = (long long*) malloc(qCards * sizeof(long long));
      for (long long j = 0; j < qCards; j ++)
        dp[i][j] = -inf;
    }

    long long answer = solve(dp, cards, 0, qCards - 1);

    printf("In game %Ld, the greedy strategy might lose by as many as %Ld points.\n", run, answer);

    free(dp);
  }
  return(0);
}