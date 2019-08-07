#include <bits/stdc++.h>
using namespace std;
#define lli long long int

lli gcd(lli a, lli b)
{
  if (!b) return(a);
  return(gcd(b, a % b));
}

pair<lli, lli> solve(lli n, lli c1, lli n1, lli c2, lli n2)
{
  lli best = (lli) 1 << 50; pair<lli, lli> b = {-1, -1};
  for (lli k = 0; n1*k <= n; k ++)
    if ((n - n1*k) % n2 == 0 && c1*k + (n - n1*k)/n2*c2 < best)
    {
      b = {k, (n - n1*k)/n2};
      best = c1*k + (n - n1*k)/n2*c2;
      break;
    }
  for (lli k = 0; n2*k <= n; k ++)
    if ((n - n2*k) % n1 == 0 && c2*k + (n - n2*k)/n1*c1 < best)
    {
      b = {(n - n2*k)/n1, k};
      best = c2*k + (n - n2*k)/n1*c1;
      break;
    }
  return(b);
}

int main()
{
  lli n;
  while (scanf("%lld", &n) && n)
  {
    lli c1, n1, c2, n2; scanf("%lld %lld\n%lld %lld", &c1, &n1, &c2, &n2);
    if (n % gcd(n1, n2) > 0) printf("failed\n");
    else
    {
      pair<lli, lli> ans = solve(n, c1, n1, c2, n2);
      printf("%lld %lld\n", ans.first, ans.second);
    }
  }
  return(0);
}