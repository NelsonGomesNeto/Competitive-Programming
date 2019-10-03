#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  lli n; scanf("%lld", &n);
  lli ans = 1;
  while (n != 1)
  {
    ans += n;
    n = n & 1LL ? 3LL*n + 1LL : n >> 1LL;
  }
  printf("%lld\n", ans);
  return 0;
}