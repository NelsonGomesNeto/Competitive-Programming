#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli mod = 1e9 + 7;

int main()
{
  int n, k;
  while (scanf("%d %d", &n, &k) != EOF)
  {
    int lo = 0, hi = n;
    lli los = 0, his = 0;
    for (int i = 0; i < k; i++, lo++, hi--)
    {
      los += lo;
      his += hi;
    }

    lli ans = 1;
    for (int i = k; i <= n; i++, lo++, hi--)
    {
      ans = (ans + max(0LL, (his - los + 1))) % mod;
      los += lo;
      his += hi;
    }
    printf("%lld\n", ans);
  }
  return 0;
}