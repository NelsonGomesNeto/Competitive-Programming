#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 4e5; int n;
lli a[maxN];

int main()
{
  scanf("%d", &n);

  lli g;
  for (int i = 0; i < n; i ++)
  {
    scanf("%lld", &a[i]);
    g = i == 0 ? a[i] : gcd(g, a[i]);
  }

  lli ans = 0;
  for (lli i = 1, end = sqrt(g); i <= end; i ++)
    if (g % i == 0)
    {
      ans ++;
      if (g % (g / i) == 0 && g / i != i)
        ans ++;
    }
  printf("%lld\n", ans);

  return(0);
}
