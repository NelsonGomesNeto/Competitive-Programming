#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, k;
lli h[maxN];

int main()
{
  while (scanf("%d %d", &n, &k) != EOF)
  {
    for (int i = 0; i < n; i ++)
      scanf("%lld", &h[i]);
    sort(h, h+n);

    lli ans = 0;
    for (int i = n - k - 1; i >= 0; i --)
      ans += h[i];
    printf("%lld\n", ans);
  }
  return 0;
}