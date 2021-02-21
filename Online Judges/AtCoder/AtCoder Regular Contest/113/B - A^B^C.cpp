#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli modPow(lli x, lli y, lli mod)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1LL) ans = ans * x % mod;
    x = x * x % mod, y >>= 1LL;
  }
  return ans;
}

int main()
{
  lli a, b, c;
  while (~scanf("%lld %lld %lld", &a, &b, &c))
  {
    int cnt[10]; memset(cnt, 0, sizeof(cnt));
    for (int i = 10; i <= 10000; i++)
    {
      lli bc = modPow(b, c, i);
      lli ans = modPow(a, bc, 10);
      cnt[ans]++;
    }
    printf("%ld\n", max_element(cnt, cnt+10) - cnt);
  }
  return 0;
}