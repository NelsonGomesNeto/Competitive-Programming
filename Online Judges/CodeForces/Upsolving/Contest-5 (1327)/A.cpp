#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli apSum(lli a1, lli an, lli n)
{
  return(n * (a1 + an) / 2.0);
}

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    lli n, k; scanf("%lld %lld", &n, &k);
    if (k == 1)
      printf("%s\n", (n & 1LL) ? "YES" : "NO");
    else
    {
      lli total = apSum(1, 2*(k - 2) + 1, k - 1);
      lli rem = n - total;
      DEBUG printf("%lld %lld %lld\n", k, total, rem);
      if (rem <= 2*(k - 2) + 1 || !(rem & 1LL))
        printf("NO\n");
      else
        printf("YES\n");
    }
  }
  return 0;
}
