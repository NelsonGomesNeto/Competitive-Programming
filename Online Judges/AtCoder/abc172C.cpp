#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int upperBound(lli arr[], int lo, int hi, lli target)
{
  while (lo < hi)
  {
    int mid = (lo + hi + 1) >> 1;
    if (arr[mid] <= target) lo = mid;
    else hi = mid - 1;
  }
  return lo;
}

int main()
{
  int n, m; lli k;
  while (scanf("%d %d %lld", &n, &m, &k) != EOF)
  {
    lli a[n], b[m];
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
    for (int i = 0; i < m; i++) scanf("%lld", &b[i]);

    lli aa[n + 1], bb[m + 1];
    aa[0] = bb[0] = 0;
    for (int i = 0; i < n; i++) aa[i + 1] = aa[i] + a[i];
    for (int i = 0; i < m; i++) bb[i + 1] = bb[i] + b[i];

    int ans = 0;
    for (int i = 0; i <= n; i++)
      if (aa[i] < k)
        ans = max(ans, i + upperBound(bb, 0, m, k - aa[i]));
    for (int i = 0; i <= m; i++)
      if (bb[i] < k)
        ans = max(ans, i + upperBound(aa, 0, n, k - bb[i]));

    printf("%d\n", ans);
  }
  return 0;
}