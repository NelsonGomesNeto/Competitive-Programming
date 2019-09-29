#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e5; int n, nsqrt;
const lli maxX = 2e14 + 1;
lli a[maxN], sum, maximum;

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    nsqrt = sqrt(n);
    sum = maximum = 0;
    for (int i = 0; i < n; i ++)
    {
      scanf("%lld", &a[i]);
      sum += a[i], maximum = max(maximum, a[i]);
    }

    lli x = maximum;
    lli z = 0;
    for (int i = 0; i < n; i ++)
      if (a[i] < x)
        z = z == 0 ? x - a[i] : gcd(z, x - a[i]);
    printf("%lld %lld\n", (x * n - sum) / z, z);
  }
  return(0);
}