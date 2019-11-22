#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e5; int n;
lli a[maxN]; int r[maxN];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    lli s = 0;
    for (int i = 0; i < n; i ++)
    {
      scanf("%lld", &a[i]);
      s += a[i];
    }

    if (s % 3LL != 0)
      printf("0\n");
    else
    {
      lli c = 0;
      for (int i = n - 1; i >= 0; i --)
      {
        c += a[i];
        r[i] = (i < n - 1 ? r[i + 1] : 0) + (c == s / 3LL);
      }

      lli ans = 0;
      c = a[0];
      for (int i = 1; i < n - 1; i ++)
      {
        if (c == s / 3LL)
          ans += r[i + 1];
        c += a[i];
      }
      printf("%lld\n", ans);
    }
  }
  return 0;
}