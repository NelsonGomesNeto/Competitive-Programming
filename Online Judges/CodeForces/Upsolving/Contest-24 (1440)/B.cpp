#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3, maxK = 1e3; int n, k;
lli a[maxN*maxK];
lli ans[maxK][maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n*k; i++)
      scanf("%lld", &a[i]);

    int mid = ((n + 1) >> 1) - 1;
    for (int j = 0; j < k; j++)
      for (int i = 0; i < mid; i++)
        ans[j][i] = a[j*mid + i];

    DEBUG
      printf("\t%d\n", mid);

    int sz = (n - 1) - mid + 1;
    for (int j = 0, ii = n*k - 1; j < k; j++)
      for (int i = n - 1; i >= mid; i--, ii--)
        ans[j][i] = a[ii];

    for (int j = 0; j < k; j++)
      sort(ans[j], ans[j]+n);

    DEBUG
      for (int j = 0; j < k; j++)
        for (int i = 0; i < n; i++)
          printf("%lld%c", ans[j][i], i < n - 1 ? ' ' : '\n');

    lli sum = 0;
    for (int j = 0; j < k; j++)
      sum += ans[j][((n + 1) >> 1) - 1];
    printf("%lld\n", sum);
  }
  return 0;
}
