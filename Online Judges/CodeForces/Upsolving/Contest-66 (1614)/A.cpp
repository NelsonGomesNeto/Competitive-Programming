#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100; int n; lli l, r, k;
lli a[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %lld %lld %lld", &n, &l, &r, &k);
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
    sort(a, a+n);

    int ans = 0;
    for (int i = 0; i < n; i++)
      if (a[i] >= l && a[i] <= r && a[i] <= k)
        k -= a[i], ans++;
    printf("%d\n", ans);
  }
  return 0;
}
