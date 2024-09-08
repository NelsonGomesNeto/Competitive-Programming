#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    lli x; scanf("%lld", &x);
    bool ended = false;
    for (lli a = 1, end = sqrt(x); a <= end && !ended; a ++)
      for (lli b = x; b >= 1 && !ended; b --)
        if (gcd(a, b) + lcm(a, b) == x)
          printf("%lld %lld\n", a, b), ended = true;
  }
  return 0;
}
/*
lcm(a, b) = x - gcd(a, b)
a * b = x / gcd(a, b) - 1
*/