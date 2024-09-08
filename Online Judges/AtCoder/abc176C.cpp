#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
lli a[maxN];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    lli maxA = 0, ans = 0;
    for (int i = 0; i < n; i++)
    {
      if (maxA > a[i]) ans += maxA - a[i];
      maxA = max(maxA, a[i]);
    }
    printf("%lld\n", ans);
  }
  return 0;
}