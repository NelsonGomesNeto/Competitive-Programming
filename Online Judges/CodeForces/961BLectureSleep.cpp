#include <bits/stdc++.h>
#define lli  long long int
using namespace std;

int main()
{
  int n, k; scanf("%d %d", &n, &k);
  int a[n]; for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
  int t[n]; for (int i = 0; i < n; i ++) scanf("%d", &t[i]);
  lli sum[n + 1]; sum[0] = 0;
  for (int i = 0; i < n; i ++)
    sum[i + 1] = sum[i] + a[i] * (!t[i]);

  lli total = 0; for (int i = 0; i < n; i ++) total += a[i] * t[i];

  lli bonus = 0;
  for (int i = 0; i <= n - k; i ++)
    bonus = max(bonus, (sum[i + k] - sum[i]));
  printf("%lld\n", total + bonus);

  return(0);
}