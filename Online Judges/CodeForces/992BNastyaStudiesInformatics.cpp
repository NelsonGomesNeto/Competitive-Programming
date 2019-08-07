#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
#define lli long long int
lli l, r, x, y;

int valid(lli a, lli b)
{
  return(a >= l && a <= r && b >= l && b <= r);
}

int main()
{
  scanf("%lld %lld %lld %lld", &l, &r, &x, &y);
  vector<lli> divisors;
  for (int i = 1; i <= sqrt(y); i ++)
    if (y % i == 0)
    {
      divisors.push_back(i);
      if (y / i != i) divisors.push_back(y / i);
    }

  DEBUG for (int i = 0; i < divisors.size(); i ++)
    printf("%lld ", divisors[i]);
  DEBUG printf("\n");
  sort(divisors.begin(), divisors.end());

  int count = 0;
  for (lli i = 0; i <= divisors.size(); i ++)
    for (lli j = 0; j <= divisors.size(); j ++)
    {
      lli a = divisors[i], b = divisors[j];
      if (valid(a, b) && gcd(a, b) == x && lcm(a, b) == y)
      {
        DEBUG printf("(%lld, %lld) -> gdc=%lld, lcm=%lld\n", a, b, gcd(a, b), lcm(a, b));
        count ++;
      }
    }

  printf("%d\n", count);
  return(0);
}