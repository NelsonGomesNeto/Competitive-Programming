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
    lli a, b, c; scanf("%lld %lld %lld", &a, &b, &c);
    lli aa = max({0LL, b - a + 1, c - a + 1}), bb = max({0LL, c - b + 1, a - b + 1}), cc = max({0LL, b - c + 1, a - c + 1});
    printf("%lld %lld %lld\n", aa, bb, cc);
  }
  return 0;
}
