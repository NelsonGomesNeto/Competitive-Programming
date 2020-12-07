#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli inf = 1e18;

lli dist(lli a, lli b, lli c)
{
  return abs(a - b) + abs(a - c) + abs(b - c);
}

int main()
{
  int t;
  scanf("%d", &t);
  while (t--)
  {
    lli a, b, c;
    scanf("%lld %lld %lld", &a, &b, &c);
    lli ans = inf;
    for (int i = -1; i <= 1; i++)
      for (int j = -1; j <= 1; j++)
        for (int k = -1; k <= 1; k++)
          ans = min(ans, dist(a + i, b + j, c + k));
    printf("%lld\n", ans);
  }

  return 0;
}
