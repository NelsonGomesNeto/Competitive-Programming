#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    lli p, a, b, c; scanf("%lld %lld %lld %lld", &p, &a, &b, &c);
    // k * a = p
    lli ans = (p / a + (p % a != 0)) * a - p;
    ans = min(ans, (p / b + (p % b != 0)) * b - p);
    ans = min(ans, (p / c + (p % c != 0)) * c - p);
    printf("%lld\n", ans);
  }
  return 0;
}
