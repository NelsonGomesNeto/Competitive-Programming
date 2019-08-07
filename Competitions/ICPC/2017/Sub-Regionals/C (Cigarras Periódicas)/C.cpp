#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli gcd(lli a, lli b)
{
  if (b == 0) return(a);
  return(gcd(b, a % b));
}

lli lcm(lli a, lli b)
{
  return((a*b) / gcd(a, b));
}

int main()
{
  lli n, l; scanf("%lld %lld", &n, &l);
  lli c[n];
  for (lli i = 0; i < n; i ++)
    scanf("%lld", &c[i]);

  lli lcmOfAll = lcm(c[0], c[1]);
  for (lli i = 2; i < n; i ++)
    lcmOfAll = lcm(lcmOfAll, c[i]);

  lli best = lcmOfAll, cBest = 1;
  for (lli i = 2; i <= l; i ++)
  {
    lli newLcm = lcm(lcmOfAll, i);
    if (newLcm > best && newLcm <= l)
    {
      best = newLcm;
      cBest = i;
    }
  }

  printf("%lld\n", cBest);

  return(0);
}