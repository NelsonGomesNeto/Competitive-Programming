#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int a, k; lli n;
ldouble b;

ldouble fix(ldouble num)
{
  lli below = floor(num / 100LL) * 100LL;
  // printf("\t%lf - %lf\n", num, num - below);
  return num - below;
}
ldouble lol(ldouble x, lli y)
{
  ldouble ans = 1;
  while (y)
  {
    if (y & 1LL) ans = ans * x;
    x = x * x, y >>= 1LL;

    // printf("\t%.15Lf %.15Lf\n", ans, x);
    x = fix(x);
    ans = fix(ans);
  }
  return ans;
}

int main()
{
  while (~scanf("%d %Lf %lld %d", &a, &b, &n, &k))
  {
    b = sqrtl(b);

    printf("%.15Lf\n", lol(a + b, n));
  }
  return 0;
}