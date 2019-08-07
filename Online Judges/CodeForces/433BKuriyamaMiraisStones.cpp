#include <bits/stdc++.h>
using namespace std;
#define lli long long int

int main()
{
  int n; scanf("%d", &n);
  lli v[n]; for (int i = 0; i < n; i ++) scanf("%lld", &v[i]);
  lli sum[n + 1]; sum[0] = 0;
  for (int i = 1; i <= n; i ++)
    sum[i] = sum[i - 1] + v[i - 1];
  sort(v, v+n);
  lli minSum[n + 1]; minSum[0] = 0;
  for (int i = 1; i <= n; i ++)
    minSum[i] = minSum[i - 1] + v[i - 1];

  int queries; scanf("%d", &queries);
  while (queries --)
  {
    int kind, l, r; scanf("%d %d %d", &kind, &l, &r);
    if (kind == 1) printf("%lld\n", sum[r] - sum[l - 1]);
    else printf("%lld\n", minSum[r] - minSum[l - 1]);
  }
  return(0);
}
