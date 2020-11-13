#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6; int m, n, k;
int corr[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d %d", &m, &n, &k);
    lli sum = 0;
    for (int i = 0; i < m; i++)
    {
      scanf("%d", &corr[i]);
      sum += corr[i];
    }
    sort(corr, corr+m);

    lli ans = sum;
    for (int i = 0; i < k; i++)
      ans += (n - corr[i]) - corr[i];
    printf("%lld\n", ans);
  }
  return 0;
}