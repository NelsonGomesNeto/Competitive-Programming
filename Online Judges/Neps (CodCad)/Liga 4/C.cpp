#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, k;
lli s[maxN];

int main()
{
  while (scanf("%d %d", &n, &k) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &s[i]);

    sort(s, s+n, greater<lli>());
    lli ans = 0;
    for (int i = 0, total = 0; total < n; i++, total += k)
    {
      ans += min((lli)k, (lli)n - total) * s[i];
    }
    printf("%lld\n", ans);
  }
  return 0;
}