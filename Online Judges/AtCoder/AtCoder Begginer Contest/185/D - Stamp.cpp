#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxM = 2e5; lli n; int m;
lli a[maxM];

int main()
{
  while (~scanf("%lld %d", &n, &m))
  {
    for (int i = 0; i < m; i++)
      scanf("%lld", &a[i]);
    sort(a, a+m);

    if (m == 0) printf("1\n");
    else if (n == m) printf("0\n");
    else
    {
      lli k = n;
      if (a[0] - 1 > 0) k = min(k, a[0] - 1);
      if (n - a[m - 1] > 0) k = min(k, n - a[m - 1]);

      for (int i = 1; i < m; i++)
        if (a[i] - a[i - 1] - 1 > 0)
          k = min(k, a[i] - a[i - 1] - 1);

      vector<lli> gaps;
      if (a[0] - 1 > 0) gaps.push_back(a[0] - 1);
      if (n - a[m - 1] > 0) gaps.push_back(n - a[m - 1]);
      for (int i = 1; i < m; i++)
        if (a[i] - a[i - 1] - 1 > 0)
          gaps.push_back(a[i] - a[i - 1] - 1);

      lli ans = 0;
      for (lli g: gaps)
        ans += g / k + (g % k != 0);
      printf("%lld\n", ans);
    }

  }
  return 0;
}
