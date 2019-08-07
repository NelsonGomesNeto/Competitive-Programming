#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e5; int n;
lli a[maxN];

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) scanf("%lld", &a[i]);
  sort(a, a+n);

  lli ans = 0;
  for (int i = lower_bound(a, a+n, 1) - a; i < n; i ++)
  {
    int pos = lower_bound(a, a+n, (a[i] >> 1) + (a[i] & 1)) - a;
    ans += i - pos;
    int lo = lower_bound(a, a+n, -2*a[i]) - a, hi = upper_bound(a, a+n, -((a[i] >> 1) + (a[i] & 1)) - 1) - a;
    if (a[hi] > -((a[i] >> 1) + (a[i] & 1))) hi --;
    ans += hi - lo + 1;
    // printf("%d %d | %d %d | %lld\n", i, pos, lo, hi, ans);
  }
  for (int i = 0; i < n && a[i] <= -1; i ++)
  {
    int aa = -a[i];
    int pos = upper_bound(a, a+n, -((aa >> 1) + (aa & 1)) - 1) - a;
    if (a[pos] > -((aa >> 1) + (aa & 1))) pos --;
    ans += pos - i;
    // printf("%d %d\n", i, pos);
  }
  printf("%lld\n", ans);

  return(0);
}
