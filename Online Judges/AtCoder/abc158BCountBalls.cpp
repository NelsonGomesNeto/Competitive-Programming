#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli n, a, b;

int main()
{
  while (scanf("%lld %lld %lld", &n, &a, &b) != EOF)
  {
    lli ans = n / (a + b) * a + min(a, n % (a + b));
    printf("%lld\n", ans);
  }
  return 0;
}