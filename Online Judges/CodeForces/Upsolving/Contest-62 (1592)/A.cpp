#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3;
lli a[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int n; lli h; scanf("%d %lld", &n, &h);
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
    sort(a, a+n);

    lli hit = a[n - 1] + a[n - 2];
    lli ans = h / hit;
    lli left = h - ans * hit;
    ans *= 2;
    ans += (left > 0) + (left > a[n - 1]);
    printf("%lld\n", ans);
  }
  return 0;
}
