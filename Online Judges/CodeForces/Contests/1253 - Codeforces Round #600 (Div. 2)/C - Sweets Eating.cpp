#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, m;
lli a[maxN], acc[maxN + 1], ans[maxN];

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < n; i ++)
      scanf("%lld", &a[i]);
    sort(a, a+n);
    for (int i = 0; i < n; i ++)
      acc[i + 1] = acc[i] + a[i];

    lli aaa[n];
    aaa[0] = a[0];
    for (int i = 1; i < n; i ++)
    {
      aaa[i] = (i - m < 0 ? 0 : aaa[i - m]) + a[i];
      DEBUG printf("%lld%c", aaa[i], i < n - 1 ? ' ' : '\n');
    }

    ans[0] = a[0];
    for (int i = 1; i < m; i ++)
      ans[i] = a[i] + ans[i - 1];
    lli d = 1, lol = 0;
    for (int i = m; i < n; i ++)
    {
      d += i % m == 0;
      ans[i] = ans[i - 1] + a[i] + aaa[i - m];
    }

    for (int i = 0; i < n; i ++)
      printf("%lld%c", ans[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}
