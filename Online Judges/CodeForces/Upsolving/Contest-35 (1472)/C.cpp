#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
lli a[maxN];
lli memo[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    for (int i = 0; i < n; i++) memo[i] = -1;
    for (int i = n - 1; i >= 0; i--)
    {
      lli ans = 0;
      int at = i;
      while (at < n)
      {
        if (memo[at] != -1)
        {
          ans += memo[at];
          break;
        }
        at += a[i];
        ans += a[i];
      }
      memo[i] = ans;
    }
    printf("%lld\n", *max_element(memo, memo+n));
  }
  return 0;
}
