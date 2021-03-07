#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  (a[i] - a[j])^2 = a[i]^2 - 2*a[i]*a[j] + a[j]^2
*/

const int maxN = 3e5; int n;
lli a[maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);
    lli sum = 0;
    for (int i = 0; i < n; i++)
      sum += a[i];

    lli ans = 0;
    for (int i = 0; i < n; i++)
    {
      ans += 2LL * (lli)(n - 1) * a[i] * a[i];
      ans -= 2LL * a[i] * (sum - a[i]);
    }
    ans >>= 1;
    printf("%lld\n", ans);
  }
  return 0;
}