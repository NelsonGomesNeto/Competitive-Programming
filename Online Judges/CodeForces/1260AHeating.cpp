#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  while (n --)
  {
    int c, s; scanf("%d %d", &c, &s);

    int ans = 0;
    while (s && c > 1)
    {
      int best = s / c;
      ans += best * best;
      s -= best, c --;
    }
    ans += s * s;

    printf("%d\n", ans);
  }
  return 0;
}