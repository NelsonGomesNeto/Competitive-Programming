#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    lli n, m; scanf("%lld %lld", &n, &m);
    
    int cycle[10], cycleSum = 0;
    for (lli i = 1; i <= 10; i ++)
      cycleSum += cycle[i - 1] = m*i % 10;

    lli ans = n / (m*10LL) * cycleSum;
    lli at = n / (m*10LL) * (m*10LL);
    while (at <= n)
    {
      ans += at % 10;
      at += m;
    }
    printf("%lld\n", ans);
  }
  return(0);
}