#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n;
  while (scanf("%d", &n) != EOF)
  {
    lli a[n];
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    sort(a, a+n, greater<lli>());
    lli ans = a[0];
    if (n > 2)
    for (int i = 1, at = 1; i < n; at++)
      for (int j = 0; j < 2; j++, i++)
        if (i < n - 1)
          ans += a[at];
    printf("%lld\n", ans);
  }
  return 0;
}