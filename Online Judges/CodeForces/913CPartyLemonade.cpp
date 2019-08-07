#include <bits/stdc++.h>
using namespace std;
#define lli long long int
lli inf = 1e18;

lli binpack(lli cost[], lli liters[], lli i, lli n, lli l)
{
  if (i == n) return(l <= 0 ? 0 : inf);
  lli ans = inf;

  ans = binpack(cost, liters, i + 1, n, l);
  ans = min(ans, binpack(cost, liters, i + 1, n, l - liters[i]) + cost[i]);

  return(ans);
}

int main()
{
  lli n, l; scanf("%lld %lld\n", &n, &l);
  lli liters[n], cost[n];
  for (int i = 0; i < n; i ++)
  {
    scanf("%lld", &cost[i]);
    liters[i] = pow(2, i);
  }

  lli small = binpack(cost, liters, 0, n, l);
  printf("%lld\n", small);

  return(0);
}