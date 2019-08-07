#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    lli k, a, b, c, d; scanf("%lld %lld %lld %lld %lld", &k, &a, &b, &c, &d);
    lli ans = 0;
    for (lli i = a; i <= b; i ++)
    {
      int start = max(k - i + 1, c);
      if (start > d) continue;
      if (i + start <= k) continue;
      ans += d - start + 1;
    }
    printf("%lld\n", ans);
  }
  return(0);
}
