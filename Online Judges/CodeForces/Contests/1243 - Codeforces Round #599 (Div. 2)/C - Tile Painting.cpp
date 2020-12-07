#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  lli n;
  while (scanf("%lld", &n) != EOF)
  {
    lli g = n;
    for (lli i = 2, end = sqrt(n); i <= end; i ++)
      if (n % i == 0)
      {
        g = gcd(g, i);
        if (i != n / i)
          g = gcd(g, n / i);
      }
    printf("%lld\n", g);
  }
  return 0;
}