#include <bits/stdc++.h>
#define lli long long int
// ap

double gpSum(lli a1, double r, lli n)
{
  return(a1 * (1 - pow(r, n)) / (1 - r));
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    lli computer, cables; scanf("%lld %lld", &computer, &cables);
    int logCables = floor(log2(cables)) + 1;
    lli reached = gpSum(1, 2, logCables);
    // printf("%d %lld\n", logCables, reached);
    while (reached > computer)
    {
      logCables --;
      reached = gpSum(1, 2, logCables);
    }
    logCables += ceil((double) (computer - reached) / cables);

    printf("%d\n", logCables);
  }
  return(0);
}