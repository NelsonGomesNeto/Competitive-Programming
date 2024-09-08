#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli l, r;

int main()
{
  while (~scanf("%lld %lld", &l, &r))
  {
    lli aa, bb, cc = -1;
    for (lli a = l; a <= r; a++)
      for (lli b = a + 1; b <= r; b++)
        for (lli c = b + 1; c <= r; c++)
          if (gcd(a, b) == 1 && gcd(b, c) == 1 & gcd(a, c) != 1)
            aa = a, bb = b, cc = c;
    if (cc != -1)
      printf("%lld %lld %lld\n", aa, bb, cc);
    else
      printf("-1\n");
  }
  return 0;
}