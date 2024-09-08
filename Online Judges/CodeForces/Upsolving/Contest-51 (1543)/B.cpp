#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
lli a[maxN], acc[maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    lli total = 0;
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &a[i]);
      total += a[i];
    }

    lli base = total / n;
    lli diff = total % n;
    for (int i = 0; i < n; i++)
      a[i] = base;
    for (int i = n - 1, hehe = diff; hehe > 0; hehe--, i--)
      a[i]++;

    for (int i = 0; i < n; i++)
      acc[i + 1] = acc[i] + a[i];

    lli ans = 0;
    for (int i = 0; i < n - 1; i++)
      ans += acc[n] - acc[i + 1] - a[i]*(n - i - 1);
    printf("%lld\n", ans);
  }
  return 0;
}
