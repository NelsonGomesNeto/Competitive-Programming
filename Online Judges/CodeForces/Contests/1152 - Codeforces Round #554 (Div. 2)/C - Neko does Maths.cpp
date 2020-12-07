#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  find k that minimizes lcm(a + k, b + k)
  Open the formulas:
    LCM:
      lcm(a, b) = a * b / gcd(a, b)
      So, you just have to test all possible gcds
    GCD:
      gcd(a, 0) = a
      gcd(a, b) = gcd(b, a mod b)
      There's anything useful here
    GCD:
      gcd(a, a) = a
      gcd(a, b) = gcd(a - b, b) if a > b
      gcd(a, b) = gcd(a, b - a) if b > a
      So, we can use this to modify gcd(a + k, b + k), let's assume a > b
      gcd(a + k, b + k) = gcd(a + k - (b + k), b + k) = gcd(a - b, b + k)
      Since gcd is the Greatest Common Divisor, the gcd can only be one of the
      divisors of (a - b).
      So for each divisor d:
        if (b % d == 0): k = 0
        else k = d - (b % d)
        (Notice that this k makes sure that (b + k) is also divisible by d)
        save the that gives the minimum lcm(a + k, b + k)
*/

lli a, b;

int main()
{
  scanf("%lld %lld", &a, &b);
  if (b > a) swap(a, b);

  lli k = 0, minimumLCM = 1e18, maximumGCD = -1e18;
  vector<lli> divisors;
  for (lli i = 1, end = sqrt(a - b); i <= end; i ++)
    if ((a - b) % i == 0)
    {
      divisors.push_back(i);
      if ((a - b) / i != i) divisors.push_back((a - b) / i);
    }

  for (lli i: divisors)
  {
    lli p = i - b % i;
    if (b % i == 0) p = 0;
    lli l = lcm(a + p, b + p);
    if (l < minimumLCM)
      k = p, minimumLCM = l;
  }
  printf("%lld\n", k);

  return(0);
}