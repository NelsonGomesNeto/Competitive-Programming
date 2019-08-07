#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli n, a, b;

pair<lli, lli> findDivisors(lli area)
{
  lli aa = 0, bb = 0;
  for (lli i = min(a, b), end = sqrt(area); i <= end; i ++)
    if (area % i == 0)
    {
      aa = a > b ? max(area / i, i) : min(area / i, i), bb = b >= a ? max(area / i, i) : min(area / i, i);
      if (aa >= a && bb >= b) break;
    }
  return(make_pair(aa, bb));
}

int main()
{
  scanf("%lld %lld %lld", &n, &a, &b);
  if (6LL*n > a*b)
  {
    lli aa = 0, bb = 0, area = 6LL*n;
    while (aa < a || bb < b)
    {
      pair<lli, lli> divisors = findDivisors(area ++);
      aa = divisors.first, bb = divisors.second;
    }
    a = aa, b = bb;
  }
  printf("%lld\n%lld %lld\n", a*b, a, b);
  return(0);
}